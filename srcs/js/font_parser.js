/**!






 __  __                                                  ____
|  \/  |   __ _  __  __   ___   _ __     ___    ___     / ___|   __ _   _ __ ___     __ _ 
| |\/| |  / _` | \ \/ /  / _ \ | '_ \   / __|  / _ \   | |  _   / _` | | '_ ` _ \   / _` |
| |  | | | (_| |  >  <  |  __/ | | | | | (__  |  __/   | |_| | | (_| | | | | | | | | (_| |
|_|  |_|  \__,_| /_/\_\  \___| |_| |_|  \___|  \___|    \____|  \__,_| |_| |_| |_|  \__,_|







 */
/**!
 *   @license © Copyright 2024, All rights reserved.
 *   @author Maxence Gama, @maxencegama
 *   @contact contact@maxencegama.dev
 */

const readFile = (fileName) => new Promise(async (resolve, reject) => {
	let b = (await fetch(fileName)).arrayBuffer();
	return resolve(b);
});

class TrueTypeCmap0 {
	format = 0;
	array = [];

	constructor(file, length) {
		for (var i = 0; i < 256; i++) {
			var glyphIndex = file.getUint8();
			// console.log("   Glyph[%s] = %s", i, glyphIndex);
			this.array.push(glyphIndex);
		}
	}

	map(charCode) {
		if (charCode >= 0 && charCode <= 255) {
			//console.log("charCode %s maps to %s", charCode, this.array[charCode]);
			return this.array[charCode];
		}
		return 0;
	}
}

class TrueTypeCmap4 {
	format = 4;
	cache = {};
	segments;

	constructor(file, length) {
		var i, segments = [];

		// 2x segcount
		var segCount = file.getUint16() / 2;

		// 2 * (2**floor(log2(segCount)))
		var searchRange = file.getUint16();
		// log2(searchRange)
		var entrySelector = file.getUint16();
		// (2*segCount) - searchRange
		var rangeShift = file.getUint16();
		// Ending character code for each segment, last is 0xffff
		for (i = 0; i < segCount; i++) {
			segments.push({
				idRangeOffset: 0,
				startCode: 0,
				endCode: file.getUint16(),
				idDelta: 0
			});
		}

		// reservePAd
		file.getUint16();

		// starting character code for each segment
		for (i = 0; i < segCount; i++) {
			segments[i].startCode = file.getUint16();
		}

		// Delta for all character codes in segment
		for (i = 0; i < segCount; i++) {
			segments[i].idDelta = file.getUint16();
		}

		// offset in bytes to glyph indexArray, or 0
		for (i = 0; i < segCount; i++) {
			var ro = file.getUint16();
			if (ro) {
				segments[i].idRangeOffset = file.tell() - 2 + ro;
			} else {
				segments[i].idRangeOffset = 0;
			}
		}

		this.segments = segments;
	}

	map(charCode) {
		if (!(charCode in this.cache)) {
			for (var j = 0; j < this.segments.length; j++) {
				var segment = this.segments[j];
				if (segment.startCode <= charCode && segment.endCode >= charCode) {
					var index, glyphIndexAddress;
					if (segment.idRangeOffset) {
						glyphIndexAddress = segment.idRangeOffset + 2 * (charCode - segment.startCode);
						this.file.seek(glyphIndexAddress);
						index = this.file.getUint16();
					} else {
						index = (segment.idDelta + charCode) & 0xffff;
					}
					// console.log("Charcode %s is between %s and %s; maps to %s (%s) roffset=%s",
					// 	charCode, segment.startCode, segment.endCode,
					// 	glyphIndexAddress, index, segment.idRangeOffset);

					this.cache[charCode] = index;
					break;
				}
			}

			if (j === this.segments.length) {
				this.cache[charCode] = 0;
			}
		}

		return this.cache[charCode];
	}
};

class Kern0Table {
	swap;
	offset;
	nPairs;
	map = {};
	oldIndex = -1;

	constructor(file, vertical, cross) {
		this.swap = vertical && !cross || !vertical && cross;
		this.file = file;
		this.offset = file.tell();
		this.nPairs = file.getUint16();
		file.getUint16(); // searchRange
		file.getUint16(); // entrySelector
		file.getUint16(); // rangeShift
		// console.log("this.nPairs", this.nPairs);
		for (var i = 0; i < this.nPairs; i++) {
			var left = file.getUint16();
			var right = file.getUint16();
			var value = file.getFword();
			// console.log("kern", left, right, value);
			// console.log("index", ((left << 16) | right), this.map[(left << 16) | right]);
			this.map[(left << 16) | right] = value;
			// console.log("Kern %s/%s->%s", left, right, value);
		}
		// console.log(this.map, Object.keys(this.map).length);
		this.reset();
	}

	reset() {
		this.oldIndex = -1;
	}

	get(glyphIndex) {
		var x = 0;
		if (this.oldIndex >= 0) {
			var ch = (this.oldIndex << 16) | glyphIndex;
			if (ch in this.map) {
				x = this.map[ch];
			}
		}
		this.oldIndex = glyphIndex;
		if (this.swap) {
			return {
				x: 0,
				y: x
			};
		} else {
			return {
				x: x,
				y: 0
			};
		}
	}
};

const assert = (test) => {
	if (!test)
		throw new Error("error: ".concat(test));
}

function BinaryReader(arrayBuffer)
{
	// assert(arrayBuffer instanceof ArrayBuffer);
	this.pos = 0;
	this.data = new Uint8Array(arrayBuffer);
	// console.log(this.data[0].toString(16),
	//     this.data[1].toString(16),
	//     this.data[2].toString(16),
	//     this.data[3].toString(16));
}

BinaryReader.prototype = {
	seek: function(pos) {
		assert(pos >= 0 && pos <= this.data.length);
		var oldPos = this.pos;
		this.pos = pos;
		return oldPos;
	},

	tell: function() {
		return this.pos;
	},

	getUint8: function() {
		assert(this.pos < this.data.length);
		return this.data[this.pos++];
	},

	getUint16: function() {
		return ((this.getUint8() << 8) | this.getUint8()) >>> 0;
	},

	getUint32: function() {
		return this.getInt32() >>> 0;
	},

	getInt16: function() {
		var result = this.getUint16();
		if (result & 0x8000) {
			result -= (1 << 16);
		}
		return result;
	},

	getInt32: function() {
		return ((this.getUint8() << 24) | 
				(this.getUint8() << 16) |
				(this.getUint8() <<  8) |
				(this.getUint8()      ));
	}, 

	getFword: function() {
		return this.getInt16();
	},

	get2Dot14: function() {
		return this.getInt16() / (1 << 14);
	},

	getFixed: function() {
		return this.getInt32() / (1 << 16);
	},

	getString: function(length) {
		var result = "";
		for(var i = 0; i < length; i++) {
			result += String.fromCharCode(this.getUint8());
		}
		return result;
	},

	getDate: function() {
		var macTime = this.getUint32() * 0x100000000 + this.getUint32();
		var utcTime = macTime * 1000 + Date.UTC(1904, 1, 1);
		return new Date(utcTime);
	},

	slice(start, length) {
		return (new BinaryReader(this.data.slice(start, start + length)));
	},

	getUnicodeString(length) {
		var result = "";
		for (var i = 0; i < length; i += 2) {
			result += String.fromCharCode(this.getUint16());
		}
		return result;
	},
};

function TrueTypeFont(arrayBuffer)
{
	this.file = new BinaryReader(arrayBuffer);
	this.tables = this.readOffsetTables(this.file);
	this.cmaps = [];
	this.kern = [];
	this.readHeadTable(this.file);
	this.readNameTable(this.file);
	this.readCmapTable(this.file);
	this.readHheaTable(this.file);
	this.readKernTable(this.file);
	this.length = this.glyphCount();
	// console.log("index", this.cmaps[0].map('m'.charCodeAt(0)));
}

TrueTypeFont.prototype = {
	readOffsetTables: function(file) {
		var tables = {};
		this.scalarType = file.getUint32();
		var numTables = file.getUint16();
		// console.log("scalar_type %d num_tables %d\n", this.scalarType, numTables);
		this.searchRange = file.getUint16();
		this.entrySelector = file.getUint16();
		this.rangeShift = file.getUint16();
		// console.log("search_range %d entry_selector %d range_shift %d\n", this.searchRange, this.entrySelector, this.rangeShift);

		for( var i = 0 ; i < numTables; i++ ) {
			var tag = file.getString(4);
			tables[tag] = {
				checksum: file.getUint32(),
				offset: file.getUint32(),
				length: file.getUint32()
			};

			// console.log(tag, tables[tag].checksum, tables[tag].offset, tables[tag].length);
			if (tag !== 'head') {
				assert(this.calculateTableChecksum(file, tables[tag].offset,
							tables[tag].length) === tables[tag].checksum);
			}
		}

		return tables;
	},

	glyphCount() {
		assert("maxp" in this.tables);
		var old = this.file.seek(this.tables["maxp"].offset + 4);
		var count = this.file.getUint16();
		this.file.seek(old);
		return count;
	},

	calculateTableChecksum: function(file, offset, length)
	{
		var old = file.seek(offset);
		var sum = 0;
		var nlongs = ((length + 3) / 4) | 0;
		while( nlongs-- ) {
			sum = (sum + (file.getUint32() & 0xffffffff)) >>> 0;
		}

		file.seek(old);
		return sum;
	},

	readHeadTable: function(file) {
		assert("head" in this.tables);
		file.seek(this.tables["head"].offset);
		// console.log("pos", file.tell());
		this.version = file.getFixed();
		this.fontRevision = file.getFixed();
		this.checksumAdjustment = file.getUint32();
		this.magicNumber = file.getUint32();
		assert(this.magicNumber === 0x5f0f3cf5);
		this.flags = file.getUint16();
		this.unitsPerEm = file.getUint16();
		this.created = file.getDate();
		this.modified = file.getDate();
		this.xMin = file.getFword();
		this.yMin = file.getFword();
		this.xMax = file.getFword();
		this.yMax = file.getFword();
		this.macStyle = file.getUint16();
		this.lowestRecPPEM = file.getUint16();
		this.fontDirectionHint = file.getInt16();
		this.indexToLocFormat = file.getInt16();
		this.glyphDataFormat = file.getInt16();
		// console.log(this.version, this.fontRevision,
		// 	this.checksumAdjustment,
		// 	this.magicNumber,
		// 	this.flags,
		// 	this.unitsPerEm,
		// 	this.created,
		// 	this.modified,
		// 	this.xMin,
		// 	this.yMin,
		// 	this.xMax,
		// 	this.yMax,
		// 	this.macStyle,
		// 	this.lowestRecPPEM,
		// 	this.fontDirectionHint,
		// 	this.indexToLocFormat,
		// 	this.glyphDataFormat);
	},

	readNameTable(file) {
		assert("name" in this.tables);
		var tableOffset = this.tables["name"].offset;
		file.seek(tableOffset);
		var format = file.getUint16(); // must be 0
		var count = file.getUint16();
		var stringOffset = file.getUint16();
		// console.log(format, count, stringOffset);
		// console.log(file.tell());
		for (var i = 0; i < count; i++) {
			var platformID = file.getUint16();
			var platformSpecificID = file.getUint16();
			var languageID = file.getUint16();
			var nameID = file.getUint16();
			var length = file.getUint16();
			var offset = file.getUint16();
			// console.log(platformID, nameID, length, offset);
			var old = file.seek(tableOffset + stringOffset + offset);
			var name;
			if (platformID === 0 || platformID === 3) {
				name = file.getUnicodeString(length);
			} else {
				name = file.getString(length);
			}
			// console.log("Name", name);
			file.seek(old);

			switch (nameID) {
				case 1:
					this.fontFamily = name;
					break;
				case 2:
					this.fontSubFamily = name;
					break;
				case 4:
					this.fullName = name;
					break;
				case 6:
					this.postscriptName = name;
					break;
			}
		}
		// console.log(this.fontFamily, this.fontSubFamily, this.fullName, this.postscriptName);
	},

	readCmapTable(file) {
		assert("cmap" in this.tables);
		var tableOffset = this.tables["cmap"].offset;
		file.seek(tableOffset);
		const cmap = {
			offset: this.tables["cmap"].offset,
			version: file.getUint16(),
			numberSubtables: file.getUint16(),
			encodingRecords: [],
			glyphIndexMap: {},
		}
		// console.log(cmap);

		// tables must be sorted by platform id and then platform specific
		// encoding.
		for (var i = 0; i < cmap.numberSubtables; i++) {
			// platforms are: 
			// 0 - Unicode -- use specific id 6 for full coverage. 0/4 common.
			// 1 - MAcintosh (Discouraged)
			// 2 - reserved
			// 3 - Microsoft
			let subTable = {
				platformID: file.getUint16(),
				platformSpecificID: file.getUint16(),
				offset: file.getUint32(),
			}
			// console.log("CMap platformid=%s specificid=%s offset=%s", subTable.platformID,
			// 	subTable.platformSpecificID, subTable.offset);
			if (subTable.platformID === 3 && (subTable.platformSpecificID <= 1)) {
				this.readCmap(file, tableOffset + subTable.offset);
			}
		}
	},

	readCmap(file, offset) {
		var oldPos = file.seek(offset);
		var format = file.getUint16();
		var length = file.getUint16();
		var language = file.getUint16();
		var cmap;
		// console.log("format", format, length);
		// console.log("    Cmap format %s length %s", format, length);
		if (format === 0) {
			cmap = new TrueTypeCmap0(file, length);
		} else if (format === 4) {
			cmap = new TrueTypeCmap4(file, length);
		}

		if (cmap) {
			this.cmaps.push(cmap);
		}

		file.seek(oldPos);
	},

	readHheaTable(file) {
		assert("hhea" in this.tables);
		var tableOffset = this.tables["hhea"].offset;
		file.seek(tableOffset);
		var version = file.getFixed(); // 0x00010000
		this.ascent = file.getFword();
		this.descent = file.getFword();
		this.lineGap = file.getFword();
		this.advanceWidthMax = file.getUint16();
		this.minLeftSideBearing = file.getFword();
		this.minRightSideBearing = file.getFword();
		this.xMaxExtent = file.getFword();
		this.caretSlopeRise = file.getInt16();
		this.caretSlopeRun = file.getInt16();
		this.caretOffset = file.getFword();
		file.getInt16(); // reserved
		file.getInt16(); // reserved
		file.getInt16(); // reserved
		file.getInt16(); // reserved
		this.metricDataFormat = file.getInt16();
		this.numOfLongHorMetrics = file.getUint16();
		// console.log(this.ascent,
		// 	this.descent,
		// 	this.lineGap,
		// 	this.advanceWidthMax,
		// 	this.minLeftSideBearing,
		// 	this.minRightSideBearing,
		// 	this.xMaxExtent,
		// 	this.caretSlopeRise,
		// 	this.caretSlopeRun,
		// 	this.caretOffset,
		// 	this.metricDataFormat,
		// 	this.numOfLongHorMetrics);
	},

	readKernTable(file) {
		if (!("kern" in this.tables)) {
			return;
		}
		var tableOffset = this.tables["kern"].offset;
		// console.log(tableOffset);
		file.seek(tableOffset);
		var version = file.getUint16(); // version 0
		var nTables = file.getUint16();

		// console.log("Kern Table version: %s", version);
		// console.log("Kern nTables: %s", nTables);
		for (var i = 0; i < nTables; i++) {
			version = file.getUint16(); // subtable version
			var length = file.getUint16();
			var coverage = file.getUint16();
			// console.log("length", length, "coverage", coverage);
			var format = coverage >> 8;
			var cross = coverage & 4;
			var vertical = (coverage & 0x1) === 0;
			// console.log("Kerning subtable version %s format %s length %s coverage: %s",
			//     version, format, length, coverage);
			var kern = null;
			if (format === 0) {
				kern = new Kern0Table(file, vertical, cross != 0);
			} else {
				// console.log("Unknown format -- skip");
				file.seek(file.tell() + length);
			}
			if (kern) {
				this.kern.push(kern);
			}
		}
		// console.log(this.kern);
	},

	getGlyphOffset: function(index) {
		assert("loca" in this.tables);
		var table = this.tables["loca"];
		var file = this.file;
		var offset, old;

		if (this.indexToLocFormat === 1) {
			old = file.seek(table.offset + index * 4);
			offset = file.getUint32();
		} else {
			old = file.seek(table.offset + index * 2);
			offset = file.getUint16() * 2;
		}

		file.seek(old);

		return offset + this.tables["glyf"].offset;
	},

	readGlyph: function(index) {
		var offset = this.getGlyphOffset(index);
		var file = this.file;

		if (offset >= this.tables["glyf"].offset + this.tables["glyf"].length) {
			return null;
		}

		assert(offset >= this.tables["glyf"].offset);
		assert(offset < this.tables["glyf"].offset + this.tables["glyf"].length);

		file.seek(offset);

		var glyph = {
			numberOfContours: file.getInt16(),
			xMin: file.getFword(),
			yMin: file.getFword(),
			xMax: file.getFword(),
			yMax: file.getFword()
		};

		assert(glyph.numberOfContours >= -1);

		// console.log(glyph.numberOfContours, "index", index);
		if (glyph.numberOfContours === -1) {
			this.readCompoundGlyph(file, glyph);
		} else {
			this.readSimpleGlyph(file, glyph);
		}
		// console.log('====================================');
		// console.log("glyph type", glyph.type);
		// console.log('====================================');
		return glyph;
	},

	readSimpleGlyph: function(file, glyph) {

		var ON_CURVE        =  1,
			X_IS_BYTE       =  2,
			Y_IS_BYTE       =  4,
			REPEAT          =  8,
			X_DELTA         = 16,
			Y_DELTA         = 32;

		glyph.type = "simple";
		glyph.contourEnds = [];
		var points = glyph.points = [];

		for( var i = 0; i < glyph.numberOfContours; i++ ) {
			glyph.contourEnds.push(file.getUint16());
		}

		// skip over intructions
		file.seek(file.getUint16() + file.tell());

		if (glyph.numberOfContours === 0) {
			return;
		}

		var numPoints = Math.max.apply(null, glyph.contourEnds) + 1;
		var flags = [];

		for( i = 0; i < numPoints; i++ ) {
			var flag = file.getUint8();
			flags.push(flag);
			points.push({
				onCurve: (flag & ON_CURVE) > 0
			});

			if ( flag & REPEAT ) {
				var repeatCount = file.getUint8();
				assert(repeatCount > 0);
				i += repeatCount;
				while( repeatCount-- ) {
					flags.push(flag);
					points.push({
						onCurve: (flag & ON_CURVE) > 0
					});
				}
			}
		}
		// console.log(points, "flags", flags, numPoints);

		function readCoords(name, byteFlag, deltaFlag, min, max) {
			var value = 0;

			// console.log(file.tell());
			for( var i = 0; i < numPoints; i++ ) {
				var flag = flags[i];
				// console.log(name, "byteflag", flag & byteFlag);
				if ( flag & byteFlag ) {
					// console.log(name, "deltaFlag", flag & deltaFlag);
					if ( flag & deltaFlag ) {
						value += file.getUint8();
					} else {
						value -= file.getUint8();
					}
					// console.log(value);
				} else if ( ~flag & deltaFlag ) {
					value += file.getInt16();
				} else {
					// value is unchanged.
				}
				// console.log(value);

				points[i][name] = value;
			}
		}

		readCoords("x", X_IS_BYTE, X_DELTA, glyph.xMin, glyph.xMax);
		readCoords("y", Y_IS_BYTE, Y_DELTA, glyph.yMin, glyph.yMax);
	},

	readCompoundGlyph(file, glyph) {
		var ARG_1_AND_2_ARE_WORDS = 1,
			ARGS_ARE_XY_VALUES = 2,
			ROUND_XY_TO_GRID = 4,
			WE_HAVE_A_SCALE = 8,
			// RESERVED              = 16
			MORE_COMPONENTS = 32,
			WE_HAVE_AN_X_AND_Y_SCALE = 64,
			WE_HAVE_A_TWO_BY_TWO = 128,
			WE_HAVE_INSTRUCTIONS = 256,
			USE_MY_METRICS = 512,
			OVERLAP_COMPONENT = 1024;

		var flags = MORE_COMPONENTS;
		var component;
		glyph.contourEnds = [];
		glyph.points = [];
		while (flags & MORE_COMPONENTS) {
			var arg1, arg2;

			flags = file.getUint16();
			component = {
				glyphIndex: file.getUint16(),
				matrix: {
					a: 1, b: 0, c: 0, d: 1, e: 0, f: 0
				},

				dest_point_index: 0,
				src_point_index: 0
			};
			// console.log('====================================');
			// console.log(flags, component);
			// console.log('====================================');

			// console.log(flags & ARG_1_AND_2_ARE_WORDS);
			if (flags & ARG_1_AND_2_ARE_WORDS) {
				arg1 = file.getInt16();
				arg2 = file.getInt16();
			} else {
				arg1 = file.getUint8();
				arg2 = file.getUint8();
			}
			// console.log(arg1, arg2);

			if (flags & ARGS_ARE_XY_VALUES) {
				component.matrix.e = arg1;
				component.matrix.f = arg2;
			} else {
				component.dest_point_index = arg1;
				component.src_point_index = arg2;
			}

			if (flags & WE_HAVE_A_SCALE) {
				component.matrix.a = file.get2Dot14();
				component.matrix.d = component.matrix.a;
			} else if (flags & WE_HAVE_AN_X_AND_Y_SCALE) {
				component.matrix.a = file.get2Dot14();
				component.matrix.d = file.get2Dot14();
			} else if (flags & WE_HAVE_A_TWO_BY_TWO) {
				component.matrix.a = file.get2Dot14();
				component.matrix.b = file.get2Dot14();
				component.matrix.c = file.get2Dot14();
				component.matrix.d = file.get2Dot14();
			}

			// console.log("Read component glyph index %s", component.glyphIndex);
			// console.log("Transform: [%s %s %s %s %s %s]", component.matrix.a, component.matrix.b,
			// 	component.matrix.c, component.matrix.d, component.matrix.e, component.matrix.f);
			var old = file.tell();
			var simpleGlyph = this.readGlyph(component.glyphIndex);
			if (simpleGlyph) {
				var pointOffset = glyph.points.length;
				for (var i = 0; i < simpleGlyph.contourEnds.length; i++) {
					glyph.contourEnds.push(simpleGlyph.contourEnds[i] +
						pointOffset);
				}
				for (i = 0; i < simpleGlyph.points.length; i++) {
					var x = simpleGlyph.points[i].x;
					var y = simpleGlyph.points[i].y;
					x = component.matrix.a * x + component.matrix.b * y +
						component.matrix.e;
					y = component.matrix.c * x + component.matrix.d * y +
						component.matrix.f;
					glyph.points.push({
						x: x, y: y, onCurve:
							simpleGlyph.points[i].onCurve
					});
				}
			}

			file.seek(old);
		}

		glyph.numberOfContours = glyph.contourEnds.length;

		if (flags & WE_HAVE_INSTRUCTIONS) {
			file.seek(file.getUint16() + file.tell());
		}

	},

	mapCode(charCode) {
		var index = 0;
		for (var i = 0; i < this.cmaps.length; i++) {
			var cmap = this.cmaps[i];
			index = cmap.map(charCode);
			if (index) {
				// console.log("mapCode", charCode, String.fromCharCode(charCode), index);
				break;
			}
		}
		return index;
	},

	getHorizontalMetrics(glyphIndex) {
		assert("hmtx" in this.tables);
		var file = this.file;
		var old = file.seek(this.tables["hmtx"].offset + 4);
		var offset = this.tables["hmtx"].offset;
		let advanceWidth, leftSideBearing;
		if (glyphIndex < this.numOfLongHorMetrics) {
			offset += glyphIndex * 4;
			old = this.file.seek(offset);
			advanceWidth = file.getUint16();
			leftSideBearing = file.getInt16();
		} else {
			// read the last entry of the hMetrics array
			old = file.seek(offset + (this.numOfLongHorMetrics - 1) * 4);
			advanceWidth = file.getUint16();
			file.seek(offset + this.numOfLongHorMetrics * 4 +
				2 * (glyphIndex - this.numOfLongHorMetrics));
			leftSideBearing = file.getFword();
		}

		this.file.seek(old);
		return {
			advanceWidth: advanceWidth,
			leftSideBearing: leftSideBearing
		};
	},

	drawSingleGlyph: function(index, ctx) {

		var glyph = this.readGlyph(index);

		if ( glyph === null || glyph.type !== "simple" ) {
			return false;
		}

		var p = 0,
			c = 0,
			first = 1;

		while (p < glyph.points.length) {
			var point = glyph.points[p];
			if ( first === 1 ) {
				ctx.moveTo(point.x, point.y);
				first = 0;
			} else {
				ctx.lineTo(point.x, point.y);
			}

			if ( p === glyph.contourEnds[c] ) {
				c += 1;
				first = 1;
			}

			p += 1;
		}

		return true;
	},

	drawGlyph(ctx, index, x, y) {
		var glyph = this.readGlyph(index);
		console.log(glyph);

		if (glyph === null) {
			return false;
		}

		var s = 0,
			p = 0,
			c = 0,
			contourStart = 0,
			prev;

		for (; p < glyph.points.length; p++) {
			var point = glyph.points[p];
			console.log(p, point);
			if (s === 0) {
				ctx.moveTo(point.x + x, point.y + y);
				ctx.arc(point.x + x, point.y + y, 10, 0, Math.PI * 2);
				s = 1;
			} else if (s === 1) {
				if (point.onCurve) {
					ctx.arc(point.x + x, point.y + y, 10, 0, Math.PI * 2);
				} else {
					s = 2;
				}
			} else {
				prev = glyph.points[p - 1];
				if (point.onCurve) {
					// ctx.arc(prev.x + x, prev.y + y, 10, 0, Math.PI * 2);
					// ctx.arc(point.x + x, point.y + y, 10, 0, Math.PI * 2);
					ctx.quadraticCurveTo(prev.x + x, prev.y + y,
						point.x + x, point.y + y);
					s = 1;
				} else {
					// ctx.arc(prev.x + x, prev.y + y, 10, 0, Math.PI * 2);
					// ctx.arc((prev.x + point.x) / 2,
					// (prev.y + point.y) / 2, 10, 0, Math.PI * 2);
					ctx.quadraticCurveTo(prev.x + x, prev.y + y,
						(prev.x + point.x) / 2 + x,
						(prev.y + point.y) / 2 + y);
				}
			}
			
			// console.log("ctx.pr.p=%s s=%s c=%s %s", p, s, c, glyph.contourEnds[c]);
			if (p === glyph.contourEnds[c]) {
				console.log("new contour", s, contourStart, p);
				if (s === 2) {
					prev = point;
					point = glyph.points[contourStart];
					if (point.onCurve) {
						// ctx.arc(prev.x + x, prev.y + y, 10, 0, Math.PI * 2);
						// ctx.arc(point.x + x, point.y + y, 10, 0, Math.PI * 2);
						ctx.quadraticCurveTo(prev.x + x, prev.y + y,
							point.x + x, point.y + y);
						} else {
							// ctx.arc(prev.x + x, prev.y + y, 10, 0, Math.PI * 2);
							// ctx.arc((prev.x + point.x) / 2 + x,
							// 	(prev.y + point.y) / 2 + y, 10, 0, Math.PI * 2);
							ctx.quadraticCurveTo(prev.x + x, prev.y + y,
								(prev.x + point.x) / 2 + x,
								(prev.y + point.y) / 2 + y);
							}
				}
				contourStart = p + 1;
				c += 1;
				s = 0;
				console.log("new contour", s, contourStart, p);
			}
		}

		return true;
	},

	transform(ctx, size) {
		ctx.scale((size / this.unitsPerEm), -(size / this.unitsPerEm));
	},

	drawText(ctx, text, x, y, size) {
		console.log("x=%s y=%s", x, y);
		ctx.save();
		ctx.translate(x, y);
		this.transform(ctx, size);
		x = 0;
		y = 0;
		this.resetKern();
		console.log("text", text, "length", text.length);
		for (var i = 0; i < text.length; i++) {
			var index = this.mapCode(text.charCodeAt(i));
			var metrics = this.getHorizontalMetrics(index);
			var kern = this.next_kern(index);
			// console.log("Metrics for %s code %s index %s: advanceWidth %s leftSideBearing %s kern: %s,%s", text.charAt(i),
			// 	text.charCodeAt(i), index, metrics.advanceWidth, metrics.leftSideBearing, kern.x, kern.y);
			if (text.charCodeAt(i) != 32)
				this.drawGlyph(ctx, index, x + kern.x,
					y + kern.y);
			x += metrics.advanceWidth;
		}
		ctx.restore();
	},

	resetKern() {
		for (var i = 0; i < this.kern.length; i++) {
			this.kern[i].reset();
		}
	},

	next_kern(glyphIndex) {
		var pt, x = 0, y = 0;
		for (var i = 0; i < this.kern.length; i++) {
			pt = this.kern[i].get(glyphIndex);
			x += pt.x;
			y += pt.y;
		}
		return { x: x, y: y };
	},

	getTextWidth(text, fontSize) {
		let totalWidth = 0;
	
		for (let i = 0; i < text.length; i++) {
			const charCode = text.charCodeAt(i);
			const charIndex = this.mapCode(charCode);
		
			if (charIndex !== -1) {
				const metrics = this.getHorizontalMetrics(charIndex);
		
				const charWidth = metrics.advanceWidth;
				totalWidth += charWidth;
			}
		}
		const adjustedWidth = totalWidth * (fontSize / this.unitsPerEm);
		return adjustedWidth;
	},

	getTextHeight(fontSize) {
		// Obtenez les métriques d'ascender et de descender de la police.
		const ascender = this.ascent;
		const descender = this.descent;
	
		// Calculez la hauteur totale du texte.
		const totalHeight = ascender - descender;
	
		// Ajustez la hauteur en fonction de la taille de la police (fontSize).
		// Le rapport entre la taille de la police et la hauteur doit être pris en compte.
		const adjustedHeight = totalHeight * (fontSize / this.unitsPerEm);
	
		return adjustedHeight;
	},
}

function ShowTtfFile(arrayBuffer)
{
	var font = new TrueTypeFont(arrayBuffer);

	var fontSize = 64;
	// let text = "Hello, wolrd! ofjero inreo - iuniu";
	let text = "Hello, World!";
	// let text = "aégçij./&;?!-14";
	// let text = "i";

	var width = font.getTextWidth(text, fontSize);
	var height = font.getTextHeight(fontSize);
	console.log(width, height);

	var container = document.getElementById("font-container");

	while (container.firstChild) {
		container.removeChild(container.firstChild);
	}

	console.info(font);

	var canvas = document.createElement("canvas");
	canvas.style.border = "1px solid gray";
	canvas.width = width;
	canvas.height = height;
	var ctx = canvas.getContext("2d");
	ctx.fillStyle = "#000000";
	ctx.lineWidth = 1;
	ctx.strokeStyle = "#0000FF";
	ctx.beginPath();
	let centerY = Math.round(font.ascent * fontSize / font.unitsPerEm);
	font.drawText(ctx, text, 0, centerY, fontSize);
	ctx.stroke();
	// ctx.fill();
	container.appendChild(canvas);
	let a = document.createElement("p");
	a.innerText = text;
	container.appendChild(a);

	// let scale = fontSize / font.unitsPerEm;
	// for( var i = 0; i < font.length; i++ ) {
		// var canvas = document.createElement("canvas");
		// canvas.style.border = "1px solid gray";
		// canvas.width = width * scale;
		// canvas.height = height * scale;
		// var ctx = canvas.getContext("2d");
		// ctx.scale(scale, -scale);
		// ctx.translate(-font.xMin, -font.yMin - height);
		// ctx.fillStyle = "#000000";
		// ctx.beginPath();
		// let i = font.mapCode("é".charCodeAt(0));
		// if (font.drawSingleGlyph(i, ctx)) {
		// 	ctx.fill();
		// 	container.appendChild(canvas);
		// }
	// }
}

(async function() {
	let buffer = await readFile("/assets/fonts/comfortaa_bold.ttf");
	ShowTtfFile(buffer);
})();

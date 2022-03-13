const src = require("fs").readFileSync("scripts/source.c").toString();

const lines = src.split(/\r?\n/);
for (const line of lines) {
    const sub = line.slice(8, line.length);
    const temp = sub.split(/\s+/);
    const name = temp[0].slice(3, temp[0].length);
    const value = temp[0];
    console.log(`${name} = ${value},`);
}
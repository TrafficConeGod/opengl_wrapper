const src = require("fs").readFileSync("scripts/source.c").toString();

const lines = src.split(/\r?\n/);
for (const line of lines) {
    const sub = line.slice(11, line.length);
    const temp = sub.split(/\s+/);
    const name = temp[0];
    const value = temp[1];
    console.log(`${name} = ${value},`);
}
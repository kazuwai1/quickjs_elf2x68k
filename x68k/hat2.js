iocs.crtmod(4, 1);
iocs.g_clr_on();
iocs.apage(0);
iocs.vpage(15);

// 160要素の配列を100で初期化（JSは0始まりなのでサイズ161確保して1〜160を使用、または0〜159にシフト可能ですが、
// sxの計算に合わせて1〜160のインデックスを維持しています）
const d = new Array(161).fill(100);

const c = [ 0, 3, 5, 7, 9, 11, 13, 15 ];
let t0, t1;
const dr = Math.PI / 180;
const zzz = [];
let r;

function draw_surface() {
    let i = 0;
    for (let y = -180; y <= 180; y += 6) {
        for (let x = -180; x <= 180; x += 4) {
            const z = zzz[i];
            
            // Luaの整数除算 `//` は Math.floor() で代用
            const sx = 81 + Math.floor(x / 3) - Math.floor(y / 6);
            const sy = 40 - Math.floor(y / 6) - Math.floor(z / 4);

            if (sx >= 1 && sx < 161) {
                if (d[sx] > sy) {
                    // cのインデックス計算。Luaのc[... + 2]をJS（0始まり）に合わせて調整
                    const cIndex = Math.floor((z + 100.0) * 0.035) + 1;
                    const color = c[cIndex] !== undefined ? c[cIndex] : 0;
                    
                    iocs.pset(sx * 3, sy * 4, color);
                    d[sx] = sy;
                }
            }
            i++;
        }
    }
}

let i = 0;
console.log("START");
t0 = Date.now(); // ミリ秒単位での取得になります

for (let y = -180; y <= 180; y += 6) {
    for (let x = -180; x <= 180; x += 4) {
        if (x === 0 && y === 0) {
            r = 0.0;
        } else {
            r = dr * Math.sqrt(x * x + y * y);
        }
        zzz[i] = 100.0 * Math.cos(r) - 30.0 * Math.cos(3.0 * r);
        i++;
    }
}

t1 = Date.now();
// Date.now() はミリ秒なので、秒単位にする場合は 1000 で割ってください
console.log("PART1 : " + ((t1 - t0) / 1000)); 
draw_surface();
console.log("END : " + ((Date.now() - t0) / 1000));
/* human68k's iocs call function */

#ifdef __human68k__
#define __DOS_INLINE__
#define __IOCS_INLINE__
#include <x68k/dos.h>
#include <x68k/iocs.h>
#endif

#include "quickjs.h"

#if 0
/* template */
static JSValue js_my_add(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    int32_t a, b;

    // 引数のバリデーションと変換
    if (JS_ToInt32(ctx, &a, argv[0]) < 0 || JS_ToInt32(ctx, &b, argv[1]) < 0) {
        return JS_EXCEPTION;
    }

    // 計算結果をJSValueとして返す
    return JS_NewInt32(ctx, a + b);
}
#endif

/* $10     _CRTMOD         CRT モード設定 */
static JSValue x68k_iocs_crtmod(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t mode, ret;
 
    // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 1 || JS_ToInt32(ctx, &mode, argv[0]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    if (mode != -1) {
        _iocs_crtmod(mode);
        ret = -1;
    } else {
        ret = _iocs_crtmod(mode);
    }

    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $90     _G_CLR_ON       グラフィック画面の初期化及び表示モードの設定 */
static JSValue x68k_iocs_g_clr_on(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k
    _iocs_g_clr_on();

    return JS_NewInt32(ctx, 0);
#else
	return JS_UNDEFINED;
#endif
}

/* $94     _GPALET         グラフィックパレット設定 */
static JSValue x68k_iocs_gpalet(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t pno, ccode, ret;
 
    // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 2 || JS_ToInt32(ctx, &pno, argv[0]) < 0 || JS_ToInt32(ctx, &ccode, argv[1]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    ret = _iocs_gpalet(pno, ccode);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

#if 0   /* 使用可能なIOCS Ver.が限定されるので実装しない */
/* $b0     _DRAWMODE       グラフィック描画モードの設定 */
static JSValue x68k_iocs_drawmode(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
}
#endif

/* $b1     _APAGE          グラフィック描画ページの設定 */
static JSValue x68k_iocs_apage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t page, ret;
 
    // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 1 || JS_ToInt32(ctx, &page, argv[0]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    ret = _iocs_apage(page);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $b2     _VPAGE          グラフィック画面表示ページの設定 */
static JSValue x68k_iocs_vpage(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t page, ret;
 
    // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 1 || JS_ToInt32(ctx, &page, argv[0]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    ret = _iocs_vpage(page);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $b3     _HOME           グラフィック画面の表示位置設定 */
static JSValue x68k_iocs_home(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t pno, x, y, ret;
 
    // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 3 || JS_ToInt32(ctx, &pno, argv[0]) < 0 || JS_ToInt32(ctx, &x, argv[1]) < 0 || JS_ToInt32(ctx, &y, argv[2]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    ret = _iocs_home(pno, x, y);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $b4     _WINDOW         グラフィック描画ウィンドウの設定 */
static JSValue x68k_iocs_window(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t x1, y1, x2, y2, ret;
 
    // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 4 || JS_ToInt32(ctx, &x1, argv[0]) < 0 || JS_ToInt32(ctx, &y1, argv[1]) < 0 ||
        JS_ToInt32(ctx, &x2, argv[2]) < 0 || JS_ToInt32(ctx, &y2, argv[3]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    ret = _iocs_window(x1, y1, x2, y2);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $b5     _WIPE           グラフィック画面のクリア */
static JSValue x68k_iocs_wipe(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t ret;
 
    ret = _iocs_wipe();
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $b6     _PSET           グラフィック画面のポイントセット */
static JSValue x68k_iocs_pset(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t x, y, c, ret;
    struct iocs_psetptr psetptr;
   
     // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 3 || JS_ToInt32(ctx, &x, argv[0]) < 0 || JS_ToInt32(ctx, &y, argv[1]) < 0 || JS_ToInt32(ctx, &c, argv[2]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    psetptr.x = x;
    psetptr.y = y;
    psetptr.color = c;

    ret = _iocs_pset(&psetptr);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $b7     _POINT          グラフィック画面のポイントゲット */
static JSValue x68k_iocs_point(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t x, y, c = -1, ret;
    struct iocs_pointptr pointptr;
   
     // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 2 || JS_ToInt32(ctx, &x, argv[0]) < 0 || JS_ToInt32(ctx, &y, argv[1]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    pointptr.x = x;
    pointptr.y = y;
    pointptr.color = c;

    ret = _iocs_point(&pointptr);
    return JS_NewInt32(ctx, ret == -1 ? ret : c);
#else
	return JS_UNDEFINED;
#endif
}
/* $b8     _LINE           グラフィック画面のライン */
static JSValue x68k_iocs_line(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t x1, y1, x2, y2, c, style, ret;
    struct iocs_lineptr lineptr;
   
     // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 6 || JS_ToInt32(ctx, &x1, argv[0]) < 0 || JS_ToInt32(ctx, &y1, argv[1]) < 0 ||
        JS_ToInt32(ctx, &x2, argv[2]) < 0 || JS_ToInt32(ctx, &y2, argv[3]) < 0 || JS_ToInt32(ctx, &c, argv[4]) < 0 || JS_ToInt32(ctx, &style, argv[5]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    lineptr.x1 = x1;
    lineptr.y1 = y1;
    lineptr.x2 = x2;
    lineptr.y2 = y2;
    lineptr.color = c;
    lineptr.linestyle = style;    

    ret = _iocs_line(&lineptr);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $b9     _BOX            グラフィック画面のボックス */
static JSValue x68k_iocs_box(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t x1, y1, x2, y2, c, style, ret;
    struct iocs_boxptr boxptr;
   
     // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 6 || JS_ToInt32(ctx, &x1, argv[0]) < 0 || JS_ToInt32(ctx, &y1, argv[1]) < 0 ||
        JS_ToInt32(ctx, &x2, argv[2]) < 0 || JS_ToInt32(ctx, &y2, argv[3]) < 0 || JS_ToInt32(ctx, &c, argv[4]) < 0 || JS_ToInt32(ctx, &style, argv[5]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    boxptr.x1 = x1;
    boxptr.y1 = y1;
    boxptr.x2 = x2;
    boxptr.y2 = y2;
    boxptr.color = c;
    boxptr.linestyle = style;    

    ret = _iocs_box(&boxptr);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $ba     _FILL           グラフィック画面のボックスフィル */
static JSValue x68k_iocs_fill(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t x1, y1, x2, y2, c, ret;
    struct iocs_fillptr fillptr;
   
     // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 5 || JS_ToInt32(ctx, &x1, argv[0]) < 0 || JS_ToInt32(ctx, &y1, argv[1]) < 0 ||
        JS_ToInt32(ctx, &x2, argv[2]) < 0 || JS_ToInt32(ctx, &y2, argv[3]) < 0 || JS_ToInt32(ctx, &c, argv[4]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    fillptr.x1 = x1;
    fillptr.y1 = y1;
    fillptr.x2 = x2;
    fillptr.y2 = y2;
    fillptr.color = c;

    ret = _iocs_fill(&fillptr);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}
/* $bb     _CIRCLE         グラフィック画面のサークル */
static JSValue x68k_iocs_circle(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t x, y, r, c, start, end, ratio, ret;
    struct iocs_circleptr circleptr;
   
     // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 7 || JS_ToInt32(ctx, &x, argv[0]) < 0 || JS_ToInt32(ctx, &y, argv[1]) < 0 ||
        JS_ToInt32(ctx, &r, argv[2]) < 0 || JS_ToInt32(ctx, &c, argv[3]) < 0 || JS_ToInt32(ctx, &start, argv[4]) < 0 ||
        JS_ToInt32(ctx, &end, argv[5]) < 0 || JS_ToInt32(ctx, &ratio, argv[6]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    circleptr.x = x;
    circleptr.y = y;
    circleptr.radius = r;
    circleptr.color = c;
    circleptr.start = start;
    circleptr.end = end;
    circleptr.ratio = ratio;

    ret = _iocs_circle(&circleptr);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $bc     _PAINT          グラフィック画面のペイント */
static JSValue x68k_iocs_paint(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t x, y, c, ret;
    struct iocs_paintptr paintptr;
    static unsigned char buffer[32*1024];  // ペイント用のバッファ
    
     // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 3 || JS_ToInt32(ctx, &x, argv[0]) < 0 || JS_ToInt32(ctx, &y, argv[1]) < 0 || JS_ToInt32(ctx, &c, argv[2]) < 0) {
        return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }
    paintptr.x = x;
    paintptr.y = y;
    paintptr.color = c;
    paintptr.buf_start = buffer;
    paintptr.buf_end = buffer + sizeof(buffer);

    ret = _iocs_paint(&paintptr);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $bd     _SYMBOL         グラフィック画面のシンボル */
const char *s;
static JSValue x68k_iocs_symbol(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
#ifdef __human68k__
    int32_t x, y, mx, my, c, t, a, ret;
    struct iocs_symbolptr symbolptr;
   
     // 引数が渡されていない、または数値への変換に失敗した場合はエラーを返す
    if (argc < 8 || JS_ToInt32(ctx, &x, argv[0]) < 0 || JS_ToInt32(ctx, &y, argv[1]) < 0 ||
        JS_ToInt32(ctx, &mx, argv[3]) < 0 || JS_ToInt32(ctx, &my, argv[4]) < 0 ||
        JS_ToInt32(ctx, &c, argv[5]) < 0 || JS_ToInt32(ctx, &t, argv[6]) < 0 || JS_ToInt32(ctx, &a, argv[7]) < 0 || (s = JS_ToCString(ctx, argv[2])) == NULL) {
            return JS_ThrowTypeError(ctx, "Invalid argument: number expected");
    }

    symbolptr.x1 = x;
    symbolptr.y1 = y;
    symbolptr.string_address = (const unsigned char *)s;
    symbolptr.mag_x = mx;
    symbolptr.mag_y = my;
    symbolptr.color = c;
    symbolptr.font_type = t;
    symbolptr.angle = a;

    ret = _iocs_symbol(&symbolptr);
    JS_FreeCString(ctx, s);
    return JS_NewInt32(ctx, ret);
#else
	return JS_UNDEFINED;
#endif
}

/* $be     _GETGRM         グラフィック画面のドット単位読み込み */
/* $bf     _PUTGRM         グラフィック画面のドット単位書き込み */

#if 0
/* 一つの関数をグローバルオブジェクトに追加 */
void add_custom_builtins(JSContext *ctx) {
    // 1. グローバルオブジェクトを取得
    JSValue global_obj = JS_GetGlobalObject(ctx);

    // 2. C関数をJSの関数オブジェクトに変換 (関数名, 引数の数, マジック値)
    JSValue my_func = JS_NewCFunction(ctx, x68k_iocs_crtmod, "iocs_crtmod", 1);

    // 3. グローバルオブジェクトのプロパティとして定義
    JS_SetPropertyStr(ctx, global_obj, "iocs_crtmod", my_func);

    // 4. 取得したグローバルオブジェクトの参照カウントを減らす
    JS_FreeValue(ctx, global_obj);
}
#endif

// 1. 関数リストの定義（内容は先ほどと同じです）
static const JSCFunctionListEntry x68k_iocs_funcs[] = {
    JS_CFUNC_DEF("crtmod", 1, x68k_iocs_crtmod),
    JS_CFUNC_DEF("g_clr_on", 0, x68k_iocs_g_clr_on),
    JS_CFUNC_DEF("gpalet", 2, x68k_iocs_gpalet),
    JS_CFUNC_DEF("apage", 1, x68k_iocs_apage),
    JS_CFUNC_DEF("vpage", 1, x68k_iocs_vpage),
    JS_CFUNC_DEF("home", 3, x68k_iocs_home),
    JS_CFUNC_DEF("window", 4, x68k_iocs_window),
    JS_CFUNC_DEF("wipe", 0, x68k_iocs_wipe),
    JS_CFUNC_DEF("pset", 3, x68k_iocs_pset),
    JS_CFUNC_DEF("point", 3, x68k_iocs_point),
    JS_CFUNC_DEF("line", 6, x68k_iocs_line),
    JS_CFUNC_DEF("box", 6, x68k_iocs_box),
    JS_CFUNC_DEF("fill", 5, x68k_iocs_fill),
    JS_CFUNC_DEF("circle", 7, x68k_iocs_circle),
    JS_CFUNC_DEF("paint", 3, x68k_iocs_paint),
    JS_CFUNC_DEF("symbol", 8, x68k_iocs_symbol),
};

// 2. 登録用メイン関数
void add_custom_builtins(JSContext *ctx) {
    // 1. グローバルオブジェクトを取得
    JSValue global_obj = JS_GetGlobalObject(ctx);

    // 2. 空の新しいJavaScriptオブジェクト `{}` を作成 (これが iocs オブジェクトになります)
    JSValue iocs_obj = JS_NewObject(ctx);

    // 3. 作成した iocs オブジェクトに関数リストを一括登録
    JS_SetPropertyFunctionList(ctx, iocs_obj, x68k_iocs_funcs, sizeof(x68k_iocs_funcs) / sizeof(x68k_iocs_funcs[0]));

    // 4. グローバルオブジェクトに "iocs" という名前で iocs オブジェクトを登録
    // ⚠️ 注意: JS_SetPropertyStr は登録に成功すると iocs_obj の所有権を消費（内部で自動解放）します
    JS_SetPropertyStr(ctx, global_obj, "iocs", iocs_obj);

    // 5. 取得したグローバルオブジェクトの参照カウントを減らす
    JS_FreeValue(ctx, global_obj);
}

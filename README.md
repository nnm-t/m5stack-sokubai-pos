# M5Stack FACES 即売会用レジもどき

M5Stack で同人誌即売会用の簡易レジを開発するプロジェクト.

M5Stack Arduino (C++14) で記述しています.

## 機能

- 商品データの JSON ファイルからの読み込み
  - サムネイル画像の表示
- 商品に対応させた RFID カードをタッチして計数
- 金額入力での売上登録
- 時刻表示
- 売上の集計, 表示
  - JSON ファイルへの記録
  - CSV ファイルへの記録 (時刻記録つき)
- バッテリ残量表示

## 必要なハードウェア

- [M5Stack FACES](https://m5stack.com/products/face)
  - Gameboy Unit を使用します.
  - 操作系自体は, ソースを改造すれば通常の M5Stack + Joystick Unit でも対応できると思います.
- [RFID Unit 2](https://docs.m5stack.com/en/unit/rfid2)
  - RFID カードの読み込みに使用します. 本体とは Grove ケーブルで接続します.
- [Proto Module](https://shop.m5stack.com/products/proto-module)
  - [Adafruit PCF8523 RTCモジュール](https://www.melonbooks.co.jp/detail/detail.php?product_id=1174493) を取り付けて GPIO26 (SDA), GPIO13 (SCL) へ配線します.
- [13.56MHz RFID Card-F08 Chip](https://m5stack.com/collections/m5-accessory/products/13-56mhz-rfid-card-f08-chip-5pcs) (日本未発売)
  - 13.56MHz RFID (Mifare 規格) カードで代用できます.
- Micro SD カード
  - 商品データの JSON ファイル, サムネイル画像, フォントファイルを保存します.

## 環境構築

Arduino IDE で M5Stack 開発ができる環境を組んで下さい.

### ライブラリ

リポジトリには含まれていないので, 下記 URL から収集します.

- [ArduinoJson 6.12](https://arduinojson.org/)
- [M5Stack Arduino Library](https://github.com/m5stack/M5Stack)
  - MFRC522_I2C
    - M5Stack サンプルコードに含まれています. Arduino IDE の `スケッチ例 -> M5Stack -> Unit -> RFID` で読み込まれる `MFRC522_I2C.h` と `MFRC522_I2C.cpp` をリポジトリのディレクトリにコピーしてください.

### フォント

標準では組み込みフォントしか表示できないので, フォントファイルを用意します.
リポジトリには含まれていないので, 自力で作成します.

詳細な手順は各所で紹介されています. Arduino IDE の `スケッチ例 -> TFT_eSPI -> Tools -> Create_Smooth_Font -> Create_font` で読み込まれるソースを [Processing](https://processing.org/) に貼り付け, ソースを編集してフォントファイルを作成します.

`M+ 1c` で動作確認を行っています. フォントファイルは `mplus-1c20.vlw` という名前で Micro SD カードに保存します.

## 商品データ

### JSON ファイル

下記の JSON ファイルを編集し, SD カードのルートディレクトリに `goods.json` という名前で保存します.

RFID カードの UUID が含まれるので, リポジトリからは外しています.

```json
{
    "goods" : 
    [
        { 
            "name" : "商品1",
            "price" : 400,
            "image_path" : "/image_1.bmp",
            "uuid" : [ 0, 0, 0, 0 ]
        },
        {
            "name" : "商品2",
            "price" : 300,
            "image_path" : "/image_2.bmp",
            "uuid" : [ 0, 0, 0, 0 ]
        }
    ]
}
```

これとは別に, 次の内容で `sales.json` という名前の JSON ファイルも SD カード上に保存しておきます.
`goods` の要素数は `goods.json` の商品の種類数と同一にします.

```json
{
  "goods": [
    0,
    0
  ],
  "amounts": [
  ]
}
```

#### データ構造

##### `goods.json`

- `goods`: 商品データのオブジェクト
  - `name`: 商品名. 日本語表示が可能.
  - `price`: 商品の単価.
  - `image_path`: サムネイル画像の Micro SD カードでのパス.
  - `uuid`: RFID カードの UUID をバイト配列 (ビッグエンディアン, 10進数) で記述する.

##### `sales.json`

- `goods`: 商品の売上点数が数値で記録される. データ作成時は商品の種類数と同じ要素数 `0` で埋める.
- `amounts`: 金額入力の売上記録が数値で入る. データ作成時は空配列でよい.

### サムネイル画像

120 x 120 の Windows Bitmap 画像を用意し, 商品データの `image_path` で指定した Micro SD カード上の場所に保存します.

## 使い方

[Wiki](https://github.com/nnm-t/m5stack-sokubai-pos/wiki) に書きました.

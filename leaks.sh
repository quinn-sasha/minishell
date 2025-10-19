#!/bin/bash

# スクリプトの実行チェック
if [ -z "$1" ]; then
    echo "Usage: $0 <valgrind_log_file>" >&2
    exit 1
fi

LOG_FILE="$1"
TEMP_FILE=$(mktemp)
TARGET_NAME="minishell"

# 1. ログからメモリリーク詳細部分のみを抽出（冗長なヘッダを排除）
awk '/LEAK SUMMARY/ {p=0} p {print} /in loss record/ {p=1} p' "$LOG_FILE" > "$TEMP_FILE"

# 2. ブロック単位で処理し、ターゲットの実行ファイル名（minishell）が含まれるブロックのみを抽出
awk '
BEGIN { block = ""; capture = 0; }

# { でブロック開始
/^==[0-9]+== \{/ {
    block = $0 "\n";
    capture = 0;
    next;
}

# } でブロック終了
/^==[0-9]+== \}/ {
    if (capture == 1) {
        print block $0;
    }
    block = "";
    capture = 0;
    next;
}

# その他の行（コールスタック）を処理
{
    # キャプチャモードでないときに、ターゲットのバイナリ名が含まれているかチェック
    # (例: ... in /home/.../minishell)
    if (capture == 0 && index($0, TARGET_NAME) > 0) {
        capture = 1;
    }
    # ブロック全体を保持
    block = block $0 "\n";
}
' TARGET_NAME="$TARGET_NAME" "$TEMP_FILE"

# 3. 一時ファイルを削除
rm -f "$TEMP_FILE"

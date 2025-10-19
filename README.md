# Micro-shell

シェルの機能は、シェルコマンドを読み取り実行すること。
bashではプログラミング言語的な機能もあるが、micro-shell はもっともよく使われる簡単なコマンドの実行のみをサポートする。

## 目次
- [定義](#定義)
- [必要な機能](#必要な機能)
- [サポートしない機能](#サポートしない機能)
- [受けつける入力の文法](#受けつける入力の文法)
	- [Simple command](#Simple_command)
	- [Pipeline](#Pipeline)
	- [Redirection](#Redirection)
 	- [Here documents](#Here_documents)
- [実行の流れ](#実行の流れ)
	- [入力を受け取る前の処理](#入力を受け取る前の処理)
 	- [トークン化処理](#トークン化処理)
  	- [解析](#解析)
	- [変数展開](#変数展開)
 	- [リダイレクト](#リダイレクト)
 	- [コマンドの実行](#コマンドの実行)
- [Shell_parameters](#Shell_parameters)
- [Signal](#Signal)

## 定義

- blank
 A space or tab character.

- control operator
A token that performs a control function. It is a newline or '|'.

- metacharacter
A character that, when unquoted, separates words. A metacharacter is
a space, tab, newline, or one of the following characters: ‘|’, ‘<’, or ‘>’.

- token
 A sequence of characters considered a single unit by the shell.
 It is either a word or an operator.

- operator
A control operator or a redirection operator. See Redirections, for a list of
redirection operators. Operators contain at least one unquoted metacharacter.

- word
A sequence of characters treated as a unit by the shell.
ords may not include unquoted metacharacters.

- name
A word consisting solely of letters, numbers, and underscores, and beginning with a letter or underscore. Names are used as shell variable and function names. Also referred to as an identifier.

- built-in
A command that is implemented internally by the shell itself, rather than by an executable program somewhere in the file system.

- environment:
> プログラムが実行される際、環境変数と呼ばれる文字列配列が渡されます。これは「名前=値」の形式で構成される名前と値のペアのリストです。


## 必要な機能

- プロンプトを表示する
- コマンドの実行履歴（heredocの場合は履歴に残らない）
- bashでは特別な意味を持つが、課題では求められていない記号は特別な意味を持たない
	- \ (backslash) or ; (semicolon)
- '(single quote)で囲まれた文字列は、一つの単語として解釈する
	- メタ文字は解釈しない
- "(single quote)で囲まれた文字列は、一つの単語として解釈する
	- メタ文字は $(環境変数展開) のみ解釈する
- redirections: <, >, <<, >>
- here document での、環境変数の展開
- pipes: | 
- 環境変数展開: $name
	- $?という環境変数に、最新の終了ステータスを保存する
- ctrl-C, ctrl-D and ctrl-\ (bashと同じような挙動にする)
- 以下の built-in command:
	-  echo with option -n
	-  cd with only a relative or absolute path
	-  pwd with no options
	-  export with no options
	-  unset with no options
	-  env with no options or arguments
	-  exit with no options


## サポートしない機能

- here documentの、環境変数展開を以外の追加機能（例えば、コマンド置換など）
- redirections: 1>, >&など
- pipes: |&
- job control: Micro-shellでは、全てのコマンドはフォアグラウンドで実行される
- バックスラッシュ（\）によるエスケープ文字の処理
- シェル変数など、環境変数以外のbashで使われている変数
- 環境変数以外の展開（brace expansion, tilde expansion, command substitution, arithmetic expansion and filename expansion)
- Word splitting での、IFSをユーザーがカスタマイズできる機能（常にIFSホワイトスペースで単語を区切る）

> 単一引用符、二重引用符、引用符なし
> これらが連結している場合は1つの引数として扱ってますね
> 

```bash
$ echo 'hello'"world"
# => helloworld
$ echo abc'def'
# => abcdef
```

## 受けつける入力の文法

```
// <pipeline> = <simple_command> ('|' <pipeline>)
// <simple_command> = <command_element>+
// <command_element> = <word> | <redirection>
// <redirection> = '>' <word>
//               | '<' <word>
//               | '>>' <word>
//               | '<<' <word>
```

- pipelineとは 1つ以上のsimple_command とその間にある | で構成される
- simple_command とは 1つ以上の<command_element>の連なりである
- command_element とは word もしくは redirection である


### Simple_command

最もよく実行されるコマンド.
空白で区切られた、word が連続したもの.
最初の単語がコマンド名で、その後に続くのは全て引数.


### Pipeline

一つ以上のコマンドを、 `|` で区切り、連結させたもの.
文法は以下の通りである：

```
command1 [ | command2 ] ...
```
command1 の出力が command2 の入力に繋がれる.
command1 のリダイレクション設定は、パイプを繋いだ後に行われる.
パイプで繋がれた各コマンドは、subshell 環境（定義を参照）で実行される. また各コマンドは非同期に実行される.
パイプラインの終了ステータスは、最後のコマンドの終了ステータスである.


### Redirection

リダイレクションは、コマンドが読み書きをするファイルを変更できる.
文法は以下の通りである:
```
redirection_operator word
```
リダイレクションは、simple command の中の任意の位置に置くことができる.
word は展開される. (TODO: shell expansion についてもう一度調べてから書き直す)
リダイレクションの設定は左から右に解釈される.
例えば、> （出力の切り替え）が連続したら、一番右のものが適用される.

例：
```
ls > out > out2
```
結果：空の out ファイルと、ls の出力結果が入った out2 が作られる.


### Here_documents

```
<< delimiter
```
delimiter が入力されるまで、ユーザーからの入力を読み込み続ける.
今まで読みこんだ全ての行を、コマンドの入力とする.
delimiter に対してはいかなる展開もしない.
例えば、
delimiter がクオートで囲まれている場合、delimiter はクオートを除外したものになる.
また読みこんだ行は展開されなくなる.

delimiter がクオートに囲まれていない場合は、読み込んだ入力は展開される.
コマンド置換はサポートしない.


## 実行の流れ

1. ターミナルからユーザーの入力を受け取る.
2. 入力を metacharacter によって分割し、トークンのリストを作る. トークンは word と operator に分類される.
3. トークンを解析して、[Simple_command](#Simple_command) を作成する.
4. 以下で述べる[変数展開](#変数展開)を行う
5. [リダイレクト](#リダイレクト)を行う
6. コマンドを実行する
7. 全てのコマンドの実行が終了するのを待って、終了ステータスを環境変数$?に代入する


### 入力を受け取る前の処理

- 環境変数を保持したデータ構造の初期化
- シグナルハンドラの設定


### トークン化処理

入力から token をつくる.
以下の定義にしたがって、word と operator に分類される.

```
blank
  A space or tab character.

control operator
  A token that performs a control function. It is a newline or '|'.

metacharacter
  A character that, when unquoted, separates words. A metacharacter is
  a space, tab, newline, or one of the following characters: ‘|’, ‘<’, or ‘>’.

token
  A sequence of characters considered a single unit by the shell.
  It is either a word or an operator.

operator
  A control operator or a redirection operator. See Redirections, for a list of
  redirection operators. Operators contain at least one unquoted metacharacter.

word
  A sequence of characters treated as a unit by the shell.
  Words may not include unquoted metacharacters.
```


token の種類は、TOKEN_OPERATOR, TOKEN_WORD, TOKEN_EOF の3つがある.
TOKEN_EOF はトークンリストの最後の要素である.


metacharacter によって、入力は分割される.
例えば、`< infile cat | cat > outfile`という入力が来たら、トークンは、
`<` -> `infile` -> `cat` -> `|` -> `cat` -> `>` -> `outfile` のように作られる.
クオートで囲まれている文字列は、1つの word としてみなす. 
トークン化処理で、クオートが閉じられていない文法エラーを検出する.
ちなみに、入力が空文字の場合、TOKEN_EOF のみ作られる.


### 変数展開

変数展開は以下の3種類ある.

上から下の順番で実行する.

1. shell parameter expansion
2. word splitting
3. quote removal

### shell parameter expansion

$記号に続く環境変数名を、環境変数の値で置き換える.

Micro-shellは基本的な環境変数の展開のみサポートしているので、${abc}d が $abc で展開されるような機能は実装しない.

```bash
# 文法
$name
# => value
```

変数名は、はアルファベット、数字、およびアンダースコアのみで構成され、先頭がアルファベットまたはアンダースコアである文字列に限定される。それ以外の文字列は無効な変数名である(変数を作れない）.

無効な変数名を展開しようとすると、$ 記号とそのあとに続く文字列がそのまま表示される.

変数名は有効だが、環境変数に存在しない変数は空文字に展開される.

bash では、bashを実行するときに引数を渡すことができる. その引数は $[数字] の表記で取得することができる. しかし Micro-shell ではこの機能は実装せずに、上記の無効な変数名と同じように元の文字列を出力する.

環境変数の中に環境変数が設定されている場合、中の環境変数が展開された状態で保持される.

```bash
$ export foo="foo"
$ export bar="$foo bar"
# $foo => foo
# $bar => foo bar (not "$foo bar")
```

#### 展開したことによる文法エラー

展開して初めて、文法エラーであることがわかる場合もある.

```bash
$ export HELLO="hello world"
$ cat < $HELLO
bash: $HELLO: ambiguous redirect

$ export EMPTY=""
$ cat < $EMPTY
bash: $EMPTY: ambiguous redirect
```

入力として特別な意味を持つ記号(パイプやリダイレクト)を環境変数に入れると、展開後には特別な意味を失っていることがわかる.

```bash
$ export PIPE_CHAR="|"
$ ls | cat | $PIPE_CHAR
|: command not found

$ export redirect_char="<"
$ ls < $redirect_char 
bash: <: No such file or directory
```

### word splitting

変数の展開によって、一つしかなかった単語が2つ以上に分割されたり、展開によって文法エラーになるような場合に対応するための処理.

展開した文字列がクオートで囲まれている場合、その文字列に対して word splitting は行わない.

例：
```bash
squinn@c1r2s6:~/project/minishell$ export TEST="'a        a'"
squinn@c1r2s6:~/project/minishell$ echo $TEST
'a a'
squinn@c1r2s6:~/project/minishell$ echo "$TEST"
'a        a'
```

そもそも展開されていなければ、word splitting は行わない（トークンのメンバに is_expanded とかいう変数いれておくと良さそう）.

Word splitting は 「IFSホワイトスペース」を区切り文字として文字列を分割する.
Micro-shell では、ユーザーが環境変数IFSにIFSホワイトスペース以外の文字を追加しても、元の動作をする.

> IFS（内部フィールド区切り文字）のホワイトスペース文字とは、上記の定義（「定義」参照）におけるホワイトスペース文字のうち、IFSの値に含まれるものを指します。スペース、タブ、改行は常にIFSホワイトスペースとみなされ、たとえそのロケールのスペースカテゴリに含まれていない場合でも同様です。
> 

例）

- 変数の値が IFSホワイトスペースのみで構成されている場合

```bash
export TAB_AND_SPACE="   "  
squinn@c6r2s4:~/project/minishell$ echo $TAB_AND_SPACE | cat -e
$
```

環境変数 TAB_AND_SPACE には空白とタブしか入っていないので、word splitting の結果空文字列になった.

ちなみに、このような変数がクオートで囲まれると、分割されなくなる.

```bash
squinn@c6r2s4:~/project/minishell$ export SPACES="       "
squinn@c6r2s4:~/project/minishell$ echo "$SPACES" | cat -e
       $
```

下も似たような入力だが、クオートがクオートで囲まれてクオートの記号としての特別な意味が失われているため、クオート内の空白が削除されている.

```bash
export SPACES='"     "'
echo $SPACES | cat -e
# out: " "
export SPACES="'     '"
echo $SPACES | cat -e
# out: ' '
```

- ２つに分割される場合

```bash
squinn@c6r2s4:~/project/minishell$ export TWO_WORDS="Hello world"
squinn@c6r2s4:~/project/minishell$ echo $TWO_WORDS
Hello world
```

- 展開した結果、文法エラーになるような場合
    - 展開した文字列のクオートが閉じらていない

### Quote removal

実行するまえに、トークンからクオート文字(`’` や `"`)を削除する.

**ただし、環境変数を展開した結果生じたクオートは削除しない.**

```bash
$ VAR='"quoted word"'
$ echo $VAR "another word"
"quoted word" another word
```

## Signal

プロセス間通信の一つ。

非同期的なイベントをプロセスに通知する手段。

## Shell_parameters

シェルで使われている変数.

**name** と **value** のペアで構成される.

もし value が指定されていなければ、空の文字列が代入される. 空の文字列も値として有効である.

```bash
export empty
echo $empty | cat -e
$ # empty string
```

`export name[=value]` で作り、`unset name` で削除できる.

**environment** は文字列の配列で、コマンドが実行されるときに渡される.

name=value の形式になっている.

環境変数と shell variables の違い (generated by AI):

| 特徴 | Shell variables | Environment variables |
| --- | --- | --- |
| 有効範囲 (スコープ) | 現在のシェルのみ | 現在のシェルと、その子プロセス |
| 設定コマンド | 変数名=値 | export 変数名=値 |
| 確認コマンド | set | env, printenv |
| 主な用途 | シェルスクリプト内での一時的な利用 | プログラム全体の設定、パスの指定など |
| 遺伝 | しない ❌ | する ✅ |

Shell parameters は shell varialbe もしくは environment variablesで、environment variables のリストが environment だという解釈を今のところもっている.

shell variables(?) は micro-shell では実装しない.

### Special parameters

Micro-shell では、 `$?` のみをサポートする.

最新のコマンドの終了ステータスに展開される. 終了ステータスの範囲は 0 ~ 255 で、0 が正常終了、それ以外は異常終了である.

| 終了ステータス | 意味 |
| --- | --- |
| 1 | 一般的なエラー |
| 2 | ビルトインコマンドの誤用 |
| 126 | コマンドを実行できなかった（実行権限がなかった） |
| 127 | コマンドが見つからなかった |
| 128 | exit に不正な値を渡した（例えば浮動小数点数） |
| 128+n | シグナル n で終了 |
| 255 | 範囲外の終了ステータス |

### シグナルを受け取る流れ

- シグナルを発生させるイベントが起こる
- OSがそのイベントを検知して、対象のプロセスにシグナルを起こる
- 実行が中断されて、登録しておいたシグナルハンドラが呼び出される
- 実行が再開する

対応するシグナルの種類：

- CTRL+c（古いUNIXでは DEL キー）を押下すると、SIGINT を送信し、デフォルトではそのプロセスを終了させる。
- CTRL+\ を押下すると、SIGQUIT を送信し、デフォルトではプロセスを終了させ[コアダンプ](https://ja.wikipedia.org/wiki/%E3%82%B3%E3%82%A2%E3%83%80%E3%83%B3%E3%83%97)させる。


### シグナルの実装

|  | コマンドの実行前(heredocも含む） | コマンドの実行中 |
| --- | --- | --- |
| Ctrl-c (SIGINT) | 新しいプロンプトを再表示する | default |
| Ctrl-\ (SIGQUIT) | 何も起こらない | default |
- 実行の初期段階で設定すること
	- SiGINTシグナルハンドラの設定
 	- rl_event_hook() に readline() がシグナルを受けっとた時の処理を行う関数を入れておく
- SIGQUITに対しては、ただ無視する設定にしておけばいい
- 実行前に、2つのシグナルハンドラをデフォルトに戻しておく


## Git push 前にテストを走らせる方法

[Gitフック](https://git-scm.com/book/ja/v2/Git-%E3%81%AE%E3%82%AB%E3%82%B9%E3%82%BF%E3%83%9E%E3%82%A4%E3%82%BA-Git-%E3%83%95%E3%83%83%E3%82%AF)というものを利用する。
Gitの特定のアクションに紐付けて、スクリプトを走らせられる。
`pre-push` という名前のスクリプトを `.git/hooks` というディレクトリに配置すると、push するたびにスクリプトが実行される。
通常は `.git/hooks` というディレクトリにスクリプトがあるが、今回はチームで共有したい。
共有の仕方は、[このサイト](https://zenn.dev/labbase/articles/60cca07076a7f6#%E3%83%95%E3%83%83%E3%82%AF%E3%81%AE%E3%82%B9%E3%82%AF%E3%83%AA%E3%83%97%E3%83%88%E3%81%AE%E5%85%B1%E6%9C%89%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6)を参考にする。

テスト内容： `make test` をして、各テストプログラムが成功したかどうかを終了条件で確認する。終了ステータスが0であれば成功、それ以外ならexitしてpushを取り止める。
テスト後は、`make clean_test` でテストディレクトリに生成されたプログラムなどを掃除できる。

スクリプト（例）：
```bash
#!/bin/bash

echo "==== Running tests before push... ===="

make test

status=$?

if [ $status -ne 0]; then
  echo "==== FAILED. Aborting push. ===="
  exit 1
fi

echo "==== PASSED. Proceeding with push. ===="
exit 0
```

もしテストをしたくない場合は、 `git push` に 以下のオプションをつける。

```bash
git push --no-verify ...
```


### テストプログラムの追加の仕方

`tests` ディレクトリ配下に、テストしたい機能の名前のディレクトリを作成する。
そのディレクトリの中に、ソースコードとMakefileを追加する。
`make test` ができるように Makefile にルールを追加する。
このルールは、コンパイルしたプログラムを実行する。
プログラムはテストの結果を終了ステータスで示す。終了ステータスが0でなければ、そこで全体のテストが終了する。

## 全体テストの方法

test.sh を実行するときは、一時的にプロンプトを表示しないようにする.
方法は、 `input = readline(NULL);` みたいにすること.

メモリリークのチェックは、以下の valgrind オプションをつける.
```
valgrind --leak-check=full --show-leak-kinds=reachable --track-origins=yes --suppressions=minishell.supp ./minishell
```

test.sh に valgrind を適用するには、以下のように実行する.
```bash
USE_VALGRIND=1 ./test.sh
```

## Reference
- https://www.gnu.org/software/bash/manual/bash.html
- https://github.com/usatie/minishell
- https://zenn.dev/labbase/articles/60cca07076a7f6#%E3%83%95%E3%83%83%E3%82%AF%E3%81%AE%E3%82%B9%E3%82%AF%E3%83%AA%E3%83%97%E3%83%88%E3%81%AE%E5%85%B1%E6%9C%89%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6



























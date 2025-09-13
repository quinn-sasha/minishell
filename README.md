# Micro-shell

シェルの機能は、シェルコマンドを読み取り実行すること。
bashではプログラミング言語的な機能もあるが、micro-shell はもっともよく使われる簡単なコマンドの実行のみをサポートする。

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

- here document: 環境変数展開を以外の追加機能（例えば、コマンド置換など）
- redirections: 1>, >&など
- pipes: |&
- job control: Micro-shellでは、全てのコマンドはフォアグラウンドで実行される

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

pipelineとは 1つ以上のsimple_command とその間にある | で構成される.
simple_command とは 1つ以上の<command_element>の連なりである.
command_element とは word もしくは redirection である.

## Simple command

最もよく実行されるコマンド.
空白で区切られた、word が連続したもの.
最初の単語がコマンド名で、その後に続くのは全て引数.

## Pipeline

一つ以上のコマンドを、 `|` で区切り、連結させたもの.
文法は以下の通りである：

```
command1 [ | command2 ] ...
```
command1 の出力が command2 の入力に繋がれる.
command1 のリダイレクション設定は、パイプを繋いだ後に行われる.
パイプで繋がれた各コマンドは、subshell 環境（定義を参照）で実行される. また各コマンドは非同期に実行される.
パイプラインの終了ステータスは、最後のコマンドの終了ステータスである.

## Redirection

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

### Here documents

```
<< delimiter
```
delimiter が入力されるまで、ユーザーからの入力を読み込み続ける.
今まで読みこんだ全ての行を、コマンドの入力とする.
delimiter に対してはいかなる展開もしない.
delimiter がクオートで囲まれている場合、delimiter はクオートを除外したものになる.
また読みこんだ行は展開されなくなる.

delimiter がクオートに囲まれていない場合は、読み込んだ入力は展開される.
コマンド置換はサポートしない.

## 実行の流れ

1. ターミナルからユーザーの入力を受け取る.
2. 入力を metacharacter によって分割し、トークンのリストを作る. トークンは word と operator に分類される.
3. トークンを解析して、simple command を作成する.
4. 以下で述べる[展開](#展開)を行う
5. [Redirection](#Redirection)を行う
6. コマンドを実行する
7. 全てのコマンドの実行が終了するのを待って、終了ステータスを環境変数$?に代入する

## Reference
- https://www.gnu.org/software/bash/manual/bash.html
- https://github.com/usatie/minishell


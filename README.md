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

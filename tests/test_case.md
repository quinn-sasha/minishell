## Evaluation sheet

### simple command without arguments

- 絶対パスで簡単なコマンドを実行する（引数なし）
- グローバル変数の数
- 空の文字列を入力
    - 何も起こらないはず
- 空白やタブのみの入力

### Arguments and histroy

- 絶対パスコマンドを引数ありで実行（クオートなし）
    - 異なるコマンド、引数で複数回テストする

### echo, exit

- echo は、-n オプションを付けて実行する
- 引数がある場合とない場合（複数回）

### Exit status

- 絶対パスでコマンドを引数ありとなしで実行し（クオートはなし）、終了ステータスを確認する
- bash と比較してねみたいなことも書いてる

```bash
squinn@c1r3s4:~/project/minishell$ /bin/ls filethatdoesntexist
/bin/ls: cannot access 'filethatdoesntexist': No such file or directory
squinn@c1r3s4:~/project/minishell$ echo $?
2
squinn@c1r3s4:~/project/minishell$ expr $? + $?
4
```

### Signals

- Try ctrl-C in an empty prompt should show a new line with a new prompt
- Try ctrl-\ in an empty prompt should not do anything
- Try ctrl-D in an empty prompt should quit minishell --> RELAUNCH!
- Try ctrl-C in a prompt after you wrote some stuff should show a new line with a new prompt
- Try ctrl-D in a prompt after you wrote some stuff should not do anything

- Try ctrl-C after running a blocking command like cat or grep without arguments
    - デフォルトの SIGQUIT が送信されて、実行が終了する
- Try ctrl-\ after running a blocking command like cat or grep without arguments
    - プロセスを終了させコアダンプさせる
- Try ctrl-D after running a blocking command like cat or grep without arguments
    - cat もしくは grep で標準入力から読み込んでいるときに ctrl-D が押されると EOF だけが書かれると、コマンドが終了する
    - ctrl-D はシグナルを送信しないので、`sleep 5` のように標準入力から読み込まないコマンドを終了させることはない

### Quote あり

- 引数をダブルクオートで囲む（変数展開はしない）
- シングルクオートで特殊な記号（environment variables, whitespaces, pipes, redirection）を囲み、特別な意味が消えていることを確認

### env

- Check if env shows you the current environment variables

### export

- Export environment variables, create new ones, and replace old ones
- Check them with env

### unset

- Export environment variables, create new ones, and replace old ones
- Use unset to remove some of them
- Check the result with env

### cd

- Use the command cd to move the working directory and check if you are in the right directory with /bin/ls
- Repeat multiple times with working and not working cd
- try '.' '..' as arguments too

### pwd

- Use the command pwd
- Repeat multiple times in multiple directories

### 相対パス

- 相対パスでコマンドを実行する
- 複雑な相対パスの組み合わせを何回も試す(e.g. `../../dir_C/a.out`)

### Environment path

- 環境変数 PATH に入っているコマンドを実行
- `unset $PATH` して、コマンドが同じように動くか確かめる（そんなコマンドはないと言われるはず）
- `$PATH` にコロン区切りで複数のディレクトリが指定された場合、シェルは左から右へ、正しい順番でコマンドを探しているか

### Redirection

- コマンドを < と > とともに実行する
- 異なるコマンド、引数で複数回実行する
    - たまに > を >> に入れ替えてみたりする
- 同じリダイレクト記号を複数個書いた入力
- << 記号をテストする

### Pipes

- コマンドをパイプで繋いで実行する (e.g. `cat file | grep bla | more`)
    - 異なるコマンドと引数で繰り返し実行する
- 失敗するコマンドで試してみる (e.g. `'ls filethatdoesntexist | grep bla | more`)
- パイプとリダイレクトを組み合わせてみる

### Crazy!

- 入力を書き、ctrl-Cを押し、enter を押して改行する
    - 期待する結果は、新たなプロンプトが表示されること
    - 失敗する場合は、readline()で読み込んだ入力がクリアされずに残っている場合（この時書いたものは、enterを押すと実行されてしまう）
- 'dsbksdgbksdghsd’ みたいな存在しないコマンドを実行して、確かにエラーが表示されることを確認する
- 大量の引数を持つコマンドを実行する

```bash
$ echo a b c d e f g h i j k l m n o p q r s t u v w x y z 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 a b c d e f g h i j k l m n o p q r s t u v w x y z
```

- あとは大量のコマンドをパイプで繋いでみるとか？
  - fdの管理ができていないとクラッシュするらしい（fdの閉じ忘れとか？）
- ctrl-c 押して、プロンプトに戻ってきたときに ctrl-d を押す
  - 終了ステータスが 0 になっていたら間違い

例）

```bash
# test.txt
apple
banana
apricot
avocado
orange

cat test.txt | grep a | grep p | grep r | grep o | wc -l
# out: 1

echo "Hello World" | tr 'a-z' 'A-Z' | tr 'A-Z' 'a-z' | tr 'a-z' 'A-Z' | tr 'A-Z' 'a-z'
# out: hello world
```

```bash
yes | cat | cat | cat | cat | cat | cat | head -n 1
```

- y だけを出力して即座に終了する
- 何が起きたか説明する
    - パイプの一番後ろにいる `head -n 1` が終了することで、その前の `cat` プロセスはパイプの読み手口が閉じれたことを知り、パイプへの書き込みが終了する
    - この流れが後ろから前に連鎖して、最終的に `yes` コマンドが終了する


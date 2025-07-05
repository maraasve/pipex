# 🔗 pipex

**pipex** is a 42 project that replicates the shell’s ability to pipe commands together using system calls like `fork`, `execve`, `pipe`, and `dup2`.

---

## 🛠️ Features

- Executes two commands with input/output redirection using a pipe
- Mimics shell behavior:  
  `./pipex file1 cmd1 cmd2 file2`  
  is equivalent to:  
  `cmd1 < file1 | cmd2 > file2`
- Bonus feature: supports chaining more than two commands
---

## 🧪 Usage

```bash
make
./pipex infile "cmd1" "cmd2" outfile
```

```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```

```bash
./pipex infile "cmd1" "cmd2" "cmd3" ... outfile
```

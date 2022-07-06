# Gattic GClient v0.57 Beta

# About

Launch Gaatic services on a barebones client.

---

# How to Git

Production branch: `master`
Stable branch: `fancy`
Development branch: `pants`

Branch from `fancy` or `pants` in order to make changes

---

# Useful Terminal Commands
Where XXXX is the process id:

## View Connections

### Linux
```
netstat -p | grep GClient
```
### Mac
```
netstat
```
or
```
lsof -nP -i4TCP:45019 | grep GClient
```

## Other

### Attach to a Process
```strace -pXXXX -s9999 -e write```

### Kill a Process
```kill -9 XXXX```

### View Stdout of a process
```
gdb -p XXXX
detach
quit
```

For Raspi x11 forwarding (on the pi):
`sudo apt install nvidia-driver`

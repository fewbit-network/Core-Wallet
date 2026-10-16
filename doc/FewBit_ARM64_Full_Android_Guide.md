
# 📲 FewBit ARM64 - Full Android Installation Guide (UserLand + Ubuntu)

## ✅ Step 1: Download UserLAnd from Play Store

[https://play.google.com/store/apps/details?id=tech.ula&hl=it](https://play.google.com/store/apps/details?id=tech.ula&hl=it)

- Select: **Ubuntu**
- Enable Storage: ✅
- Desktop Environment: **Minimal**
- Connection Type: **Terminal**

## ✅ Step 2: Update Ubuntu Packages

```bash
sudo apt update && sudo apt upgrade -y
```

## ✅ Step 3: Install unzip and nano

```bash
sudo apt install unzip nano -y
```

## ✅ Step 4: Download and Extract the FewBit ARM64 Wallet

```bash
cd
wget https://github.com/fewbit-network/Core-Wallet/releases/download/GENESIS/FewBit-v6.6.6.6-Linux-ARM-64-bit.tar.gz
tar -xnf FewBit-v6.6.6.6-Linux-ARM-64-bit.tar.gz
rm -r FewBit-v6.6.6.6-Linux-ARM-64-bit.tar.gz
cd
```

## ✅ Step 5: Download and Extract the Bootstrap (Fast Blockchain Sync)

```bash
mkdir .fewbitcore && cd .fewbitcore
wget https://github.com/fewbit-network/Core-Wallet/releases/download/GENESIS/FewBit-BootStrap.tar.gz
tar -xvf FewBit-BootStrap.tar.gz
rm -r FewBit-BootStrap.tar.gz
```

## ✅ Step 6: Create your fewbit.conf file (Change user and password)

```bash
nano fewbit.conf
```

Paste the following (edit with your own user and password):

```
rpcuser=choose_your_user
rpcpassword=choose_your_password
rpcport=1154
rpcallowip=127.0.0.1
server=1
daemon=1
listen=1
```

Save and exit with: `CTRL + X`, then `Y`, then `Enter`

## ✅ Step 7: Start the FewBit Daemon

```bash
cd
./fewbitd
```

Wait a few seconds, then check network status:

```bash
./fewbit-cli getnetworkinfo
./fewbit-cli getblockchaininfo
```

If synced: `blocks` and `headers` will be equal ✅

## ✅ Step 8: Create a FewBit Address for the Promotion

```bash
./fewbit-cli getnewaddress "Promo"
```

Take a screenshot of your new address and post it on Discord to get **50 FBIT** 🚀
https://discord.gg/aHZs9fndQc

## ✅ Step 9: Secure and Backup Your Wallet

```bash
./fewbit-cli encryptwallet "YourStrongPassword"
./fewbit-cli backupwallet FewBit.dat
```

Keep both your password and the backup file safe!

## ✅ Step 10: Useful Commands

- Start the wallet:

```bash
./fewbitd
```

- Stop the wallet:

```bash
./fewbit-cli stop
```

- View all available commands:

```bash
./fewbit-cli help
```

## ✅ Bonus:

This method works on any **modern Android phone** with ARM64 and Ubuntu via UserLAnd.

A **full video tutorial** will be published soon on Discord. Stay tuned!

# 📲 Android Mining Guide for FewBit (FBIT)

Turn your Android phone into a FBIT miner and contribute to the FewBit Network — anywhere, anytime.

---

## ✅ Requirements

* 📱 An Android smartphone with a decent CPU (mid-range or better recommended)
* 🌐 A stable internet connection (Wi-Fi highly recommended)
* 💼 A FewBit wallet address to receive mining rewards

---

## 📅 Step 1: Install Required Apps

1. Download **UserLAnd** from the Google Play Store
2. (Optional) Install **ConnectBot** or any terminal app if prompted

---

## 🛠️ Step 2: Set Up Ubuntu in UserLAnd

1. Open **UserLAnd**
2. Create a new session with the following settings:

   * Distribution: `Ubuntu`
   * Enable Storage access: `Yes`
   * Desktop environment: `Minimal`
   * Connection type: `Terminal`
3. Wait for the environment to initialize and the terminal to open

---

## ⚙️ Step 3: Install Dependencies

Once inside the Ubuntu terminal (in UserLAnd), run:

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install git build-essential cmake libuv1-dev libssl-dev libhwloc-dev -y
```

---

## 🧱 Step 4: Download and Build XMRig for GhostRider

```bash
git clone https://github.com/xmrig/xmrig.git
cd xmrig
mkdir build
cd build
cmake ..
make -j$(nproc)
```

> ⚠️ This may take 10–30 minutes depending on your phone's CPU

---

## 🔁 Step 5: Start Mining FewBit (FBIT)

After the build is complete, launch the miner:

```bash
./xmrig --algo ghostrider --url stratum+tcp://pool.fewbit.online:5180 --user YOUR_FBIT_ADDRESS.Your_Worker --pass x
```

> Replace `YOUR_FBIT_ADDRESS.Your_Worker` with your actual FewBit wallet address.

---

## ♻️ Step 6: Keep Mining Active

* Go to Android settings and disable screen timeout or sleep
* Keep the phone connected to power at all times
* Avoid switching apps while mining

---

## 🧪 Tips

* 🔌 Use old phones with battery issues by keeping them plugged in 24/7
* 🔥 Place the phone on a ventilated or metal surface to reduce heat
* 📶 Never mine over mobile data — use Wi-Fi only
* 🚫 Don't run other heavy apps during mining

---

## 🛡️ Stay Safe

* Keep mining process running and avoid interruptions
* Use the phone only for mining if possible
* Monitor temperatures to prevent overheating

---

## 🧱 Join the Forge

Every CPU counts. Even your old smartphone can help secure the FewBit blockchain.

**Don't throw away your phone. Forge it into a FewBit miner.**

Need help? Ask in the `#📲│android-mining` channel on our Discord.

**Together we forge blocks — and legends.**

#ClipD - Clipboard Manager (In Development)

ClipD is a lightweight and minimal clipboard manager application developed using *C++ and Qt5*, designed to help users efficiently manage copied text snippets. It aims to offer simplicity, performance, and essential clipboard features in a clean and user-friendly interface.

> ⚠️ *Note:* This project is still under development and not yet feature-complete.

---

✨ Features

- 📝 *Live Clipboard Monitoring* – Automatically detects and stores copied text.
- 🧾 *List of Copied Snippets* – Keeps a history of your copied items.
- ➕ *Smart Preview* – Shows the first 15 words of each copied text with ellipsis (`...`).
- 🔍 *Detail View* – Allows viewing the full copied text in a separate window.
- 📋 *One-Click Copy* – Click on any item to re-copy it to the clipboard.
- 🎯 *System Tray Integration* – Runs silently in the background, accessible from the tray (Planned).
- 🚀 *Fast & Lightweight* – Optimized for low-spec systems and minimal resource usage.

---

🧠 Benefits

- Increase productivity by avoiding re-copying the same content.
- Useful for programmers, writers, and students who deal with repetitive text.
- Works well on *Linux* with limited resources (e.g., Atom CPUs and <2GB RAM).
- Simple and elegant design with no clutter.

---

🔧 Installation & Usage

> Currently, this project is being tested and built manually. Automated installers will be provided later.

To compile:

```bash
qmake project.pro && make && make clean
./Clipd
```

Dependencies:
- Qt5 (QtWidgets, QtGui, QtCore)
- g++

---

📌 Roadmap

- [x] Basic UI and layout
- [x] Clipboard text capture
- [ ] Full text view window
- [ ] System tray support
- [ ] Settings page (limit history, theme toggle, etc.)
- [ ] Save history to disk

---

👨‍💻 Author

Made with ❤️ by *Yassin* (YasDev)  
Feel free to contribute or suggest features via issues or pull requests.

---

📜 License

This project will be licensed under an open-source license once it reaches a stable version. (MIT)

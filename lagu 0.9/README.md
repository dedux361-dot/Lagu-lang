# 🐛 Lagu Language (v0.9)
> **Lagu — это просто! У программирования есть лёгкость. ✨**  
> *(Lagu is simple! Programming has never been so lightweight.)*

---

## 🇷🇺 Описание проекта (Russian)
**Lagu** — это ультра-компактный, лаконичный и быстрый язык программирования, написанный на C++. Он создан для тех, кто ценит минимализм, лёгкость и скорость. 

Все математические функции в Lagu сокращены всего до 2 букв, а уникальная встроенная система шансов делает его идеальным инструментом для геймдизайнеров. Теперь можно настраивать дроп и редкость предметов в играх без громоздких стен из условий `if/else`.

### ✨ Главные фичи:
- **Ультра-короткий синтаксис**: Математика строго из 2 букв (`sq`, `po`, `rn`).
- **Лёгкие циклы**: Удобное повторение команд через дефис `-` (`fo`, `cycle`).
- **Геймдизайн «из коробки»**: Мощная функция шансов `rdch` для создания лутбоксов.
- **Свой маскот**: Веселый синий червячок, который официально подсвечивает твои файлы `.lagu` прямо в VS Code!

---

## 🇬🇧 Project Description (English)
**Lagu** is an ultra-compact, lightweight, and fast programming language built from scratch in C++. It is designed for those who love minimalism, efficiency, and elegant simplicity.

All mathematical operations in Lagu are strictly reduced to just 2 letters. Moreover, its unique built-in chance system makes it the ultimate tool for game designers who want to easily configure drop rates and loot boxes without writing massive walls of complex `if/else` code.

### ✨ Key Features:
- **Ultra-short syntax**: Math operations take only 2 letters (`sq`, `po`, `rn`).
- **Lightweight loops**: Repeat commands effortlessly using the dash `-` operator (`fo`, `cycle`).
- **Game Dev ready**: Powerful chance-based random function `rdch` for loot mechanics.
- **Custom Mascot**: A happy blue worm that highlights your `.lagu` files directly inside VS Code!

---

## ⚙️ Синтаксис и Команды / Syntax & Commands

### 📥 Ввод и Вывод / I/O
- `dis(...)` — Вывод текста или результата математики на экран (Display).
- `lac("переменная")` — Остановка программы и ввод числа с клавиатуры в переменную.

### 🔁 Циклы / Loops
- `cycle(N) - команда` — Повторить команду ровно N раз.
- `fo(от, до) - команда` — Цикл со счетчиком, где текущий шаг сохраняется в переменную `i`.

### 🧮 Двухбуквенная математика / 2-Letter Math
- `po(x, y)` — Возведение числа x в степень y.
- `sq(x)` — Квадратный корень из числа.
- `ab(x)` — Модуль числа (убирает минус).
- `rn(x)` — Округление до ближайшего целого.
- `cl(x)` — Округление вверх (потолок).
- `fl(x)` — Округление вниз (пол).

### 🎲 Рандом и Геймдизайн / Random & GameDev
- `rd(от, до)` — Генерация обычного случайного целого числа.
- `rdch(шанс, от1 to до1, от2 to до2)` — Уникальная функция шансов.  
  *Пример:* `rdch(50, 1 to 5, 5 to 1050)` — с шансом 50% выдаст число от 1 до 5, и с шансом 50% — от 5 до 1050.

---

## 🚀 Пример программы / Code Example (main.lagu)

```text
dis(--- Тестируем систему шансов rdch ---)
dis(Выбрасываем 10 чисел с шансом 50 на 50 до 5 или до 1050:)
fo(1, 10) - dis(rdch(50, 1 to 5, 5 to 1050))
```
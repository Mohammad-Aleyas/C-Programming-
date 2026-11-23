# Library Book Management System — C Programming Capstone (`CSA0213`)

## Course & Team Details
- **Course:** CSA0213 – C Programming
- **Faculty Guide:** Uma Maheswara Rao
- **Team Members:**
  1. **Mohammad Aleyas** (192521220)
  2. **K. Santhosh Kumar** (191260363)
  3. **B. Mahesh Kumar** (1925260023)

---

## Repository Structure
All core business logic, CRUD operations, search/filtering, fine calculation, and persistent file storage are implemented in modular C files inside `src/`:

```text
Library-Management-System-C-Project/
├── src/
│   ├── library.h          # Struct definitions (Book, Member, IssueRecord) & prototypes
│   ├── storage.c          # Binary file handling (books.dat, members.dat, issues.dat) & default seed data
│   ├── books.c            # Module 1: Add, View, Edit, Delete & Search/Filter Books
│   ├── members.c          # Module 2: Register, View, Edit, Delete & Search Members
│   ├── circulation.c      # Module 3: Issue Books, View Active Loans, Return & Fine Engine (Rs.10/day)
│   ├── reports.c          # Module 4: Dashboard KPIs, Audit Log & Export to Library_Audit_Report.txt
│   └── main.c             # Menu-driven CLI entry point (switch-case & do-while loop)
├── web-demo/
│   ├── index.html         # Optional frontend UI prototype
│   ├── css/style.css      # UI stylesheet
│   └── js/demo.js         # UI preview script
├── Makefile               # One-command build configuration
├── .gitignore             # Ignores compiled executables & generated .dat/.txt runtime files
└── README.md              # Project documentation & compilation guide
```

---

## C Programming Concepts Demonstrated (For Viva & Evaluation)
1. **Structures (`typedef struct`)**: `Book`, `Member`, and `IssueRecord` group heterogeneous fields cleanly.
2. **Arrays of Structures**: `books[MAX_BOOKS]`, `members[MAX_MEMBERS]`, and `issues[MAX_ISSUES]` store records in memory.
3. **Pointers & Pass-by-Reference**: Used in `editBook()` / `editMember()` (`Book *b`, `Member *m`) and `FILE *` streams.
4. **Modular Multi-File Architecture**: Separated into header (`.h`) and 6 `.c` source files across all 4 modules.
5. **Binary & Text File Handling**: `fopen`, `fwrite`, `fread`, `fprintf`, and `fclose` persist database state in `.dat` files and export audit logs to `.txt`.
6. **Control Flow & String Operations**: `do-while`, `switch-case`, `if-else`, `strcmp`, `strstr`, and `snprintf`.

---

## How to Compile & Run in VS Code
1. Open the **`Library-Management-System-C-Project`** folder in VS Code (`File -> Open Folder...`).
2. Open the integrated terminal (`Ctrl + ~` or `Terminal -> New Terminal`).
3. Compile all C modules together with GCC:
   ```bash
   gcc src/main.c src/storage.c src/books.c src/members.c src/circulation.c src/reports.c -o library_system
   ```
4. Run the program:
   - **Windows:** `library_system.exe`
   - **Mac / Linux:** `./library_system`

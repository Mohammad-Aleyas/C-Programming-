# Library Book Management System (Capstone Project)

## Course & Team Details
- **Course:** CSA0213 – C Programming
- **Guided By:** Uma Maheswara Rao
- **Team Members:**
  1. Mohammad Aleyas (192521220)
  2. K. Santhosh Kumar (191260363)
  3. B. Mahesh Kumar (1925260023)

## Folder & File Structure (Modular Architecture)
```
Library-Management-System/
├── index.html                  # Main dashboard HTML layout & modals
├── css/
│   └── style.css               # Custom styling & print audit report stylesheet
├── js/
│   ├── storage.js              # Sample dataset & LocalStorage persistence
│   ├── books.js                # Module 1: Book catalog CRUD & category filtering
│   ├── members.js              # Module 2: Member directory registration & search
│   ├── circulation.js          # Module 3: Issue/Return workflow & ₹10/day fine engine
│   ├── reports.js              # Module 4: Audit log & overdue fine reporting
│   └── app.js                  # Tab navigation, toast notifications & KPI counters
├── c-backend/
│   ├── library.h               # C header file with struct definitions & prototypes
│   ├── library_functions.c     # C modular functions & binary file handling (.dat)
│   └── main.c                  # C menu-driven entry point (switch-case loop)
├── README.md                   # Setup & documentation
└── .gitignore                  # Ignores compiled binaries & temporary files
```

## How to Run in VS Code
1. Extract this ZIP folder and open **`Library-Management-System`** in VS Code (`File -> Open Folder...`).
2. **Web Application Demo:** Open `index.html` and click **Go Live** (Live Server extension) or open `index.html` directly in your browser.
3. **C Backend Compilation:** Open the VS Code terminal (`Ctrl + ~`), navigate to `c-backend`, and run:
   ```bash
   cd c-backend
   gcc main.c library_functions.c -o library_system
   ./library_system
   ```

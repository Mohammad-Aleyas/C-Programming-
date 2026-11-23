// MODULE 1: BOOK INVENTORY MANAGEMENT
function openBookModal(isEdit = false, bookId = null) {
    const form = document.getElementById('bookForm');
    form.reset();
    if (isEdit && bookId) {
        const book = books.find(b => b.id === bookId);
        document.getElementById('bookModalTitle').innerText = 'Edit Book Details';
        document.getElementById('book-edit-id').value = book.id;
        document.getElementById('book-id').value = book.id;
        document.getElementById('book-id').disabled = true;
        document.getElementById('book-title').value = book.title;
        document.getElementById('book-author').value = book.author;
        document.getElementById('book-category').value = book.category;
        document.getElementById('book-qty').value = book.qty;
    } else {
        document.getElementById('bookModalTitle').innerText = 'Add New Book';
        document.getElementById('book-edit-id').value = '';
        document.getElementById('book-id').disabled = false;
    }
    openModal('bookModal');
}

function handleSaveBook(e) {
    e.preventDefault();
    const editId = document.getElementById('book-edit-id').value;
    const id = document.getElementById('book-id').value.trim();
    const title = document.getElementById('book-title').value.trim();
    const author = document.getElementById('book-author').value.trim();
    const category = document.getElementById('book-category').value;
    const qty = parseInt(document.getElementById('book-qty').value);

    if (editId) {
        const book = books.find(b => b.id === editId);
        const diff = qty - book.qty;
        book.title = title;
        book.author = author;
        book.category = category;
        book.qty = qty;
        book.available = Math.max(0, book.available + diff);
        showToast('Book Updated', `Successfully updated "${title}".`);
    } else {
        if (books.some(b => b.id === id)) {
            showToast('Error', `Book ID "${id}" already exists!`, true);
            return;
        }
        books.push({ id, title, author, category, qty, available: qty });
        showToast('Book Added', `Successfully added "${title}" to catalog.`);
    }

    saveData();
    closeModal('bookModal');
}

function deleteBook(id) {
    if (confirm('Are you sure you want to delete this book?')) {
        books = books.filter(b => b.id !== id);
        saveData();
        showToast('Book Deleted', 'Book removed from catalog.');
    }
}

function renderBooks() {
    const query = document.getElementById('search-book-input').value.toLowerCase();
    const cat = document.getElementById('filter-category').value;
    const tbody = document.getElementById('books-table-body');
    tbody.innerHTML = '';

    const filtered = books.filter(b => {
        const matchesSearch = b.title.toLowerCase().includes(query) || b.author.toLowerCase().includes(query) || b.id.toLowerCase().includes(query);
        const matchesCat = cat === '' || b.category === cat;
        return matchesSearch && matchesCat;
    });

    if (filtered.length === 0) {
        tbody.innerHTML = `<tr><td colspan="6" class="p-6 text-center text-slate-400">No books found in inventory.</td></tr>`;
        return;
    }

    filtered.forEach(b => {
        tbody.innerHTML += `
            <tr class="hover:bg-slate-50 transition">
                <td class="p-4 font-mono font-semibold text-blue-600">${b.id}</td>
                <td class="p-4">
                    <p class="font-bold text-slate-900">${b.title}</p>
                    <p class="text-xs text-slate-500">By ${b.author}</p>
                </td>
                <td class="p-4"><span class="bg-slate-100 text-slate-700 text-xs px-3 py-1 rounded-full font-medium">${b.category}</span></td>
                <td class="p-4 text-center font-bold">${b.qty}</td>
                <td class="p-4 text-center"><span class="bg-emerald-50 text-emerald-700 text-xs px-3 py-1 rounded-full font-bold">${b.available} available</span></td>
                <td class="p-4 text-right space-x-2 no-print">
                    <button onclick="openBookModal(true, '${b.id}')" class="text-blue-600 hover:text-blue-800 p-1.5"><i class="fa-solid fa-pen"></i></button>
                    <button onclick="deleteBook('${b.id}')" class="text-rose-600 hover:text-rose-800 p-1.5"><i class="fa-solid fa-trash"></i></button>
                </td>
            </tr>
        `;
    });
}

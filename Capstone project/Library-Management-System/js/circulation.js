// MODULE 3: BOOK ISSUE & RETURN CIRCULATION
function calculateFine(dueDateStr) {
    const due = new Date(dueDateStr);
    const today = new Date();
    const diffTime = today - due;
    const diffDays = Math.ceil(diffTime / (1000 * 60 * 60 * 24));
    if (diffDays > 0) {
        return diffDays * 10;
    }
    return 0;
}

function populateIssueDropdowns() {
    const bookSelect = document.getElementById('issue-book-id');
    const memberSelect = document.getElementById('issue-member-id');

    bookSelect.innerHTML = '<option value="">-- Choose Available Book --</option>';
    books.filter(b => b.available > 0).forEach(b => {
        bookSelect.innerHTML += `<option value="${b.id}">${b.title} (Available: ${b.available})</option>`;
    });

    memberSelect.innerHTML = '<option value="">-- Choose Member --</option>';
    members.forEach(m => {
        memberSelect.innerHTML += `<option value="${m.id}">${m.name} (${m.id})</option>`;
    });
}

function handleIssueBook(e) {
    e.preventDefault();
    const bookId = document.getElementById('issue-book-id').value;
    const memberId = document.getElementById('issue-member-id').value;
    const days = parseInt(document.getElementById('issue-days').value);

    const book = books.find(b => b.id === bookId);
    const member = members.find(m => m.id === memberId);

    if (!book || book.available <= 0) {
        showToast('Error', 'Selected book is not available for issue!', true);
        return;
    }

    book.available -= 1;

    const issueDateObj = new Date();
    const dueDateObj = new Date();
    dueDateObj.setDate(issueDateObj.getDate() + days);

    const txnId = `TXN-${Math.floor(100 + Math.random() * 900)}`;
    issuedBooks.push({
        txnId,
        bookId: book.id,
        bookTitle: book.title,
        memberId: member.id,
        memberName: member.name,
        issueDate: issueDateObj.toISOString().split('T')[0],
        dueDate: dueDateObj.toISOString().split('T')[0],
        status: 'Active'
    });

    saveData();
    document.getElementById('issueForm').reset();
    populateIssueDropdowns();
    showToast('Book Issued', `Successfully issued "${book.title}" to ${member.name}.`);
}

function returnBook(txnId) {
    const txn = issuedBooks.find(i => i.txnId === txnId);
    if (!txn) return;

    const fine = calculateFine(txn.dueDate);
    txn.status = 'Returned';

    const book = books.find(b => b.id === txn.bookId);
    if (book) {
        book.available = Math.min(book.qty, book.available + 1);
    }

    saveData();
    showToast('Book Returned', `Book successfully returned. Fine collected: ₹${fine}`);
}

function renderIssuedBooks() {
    const tbody = document.getElementById('issued-table-body');
    tbody.innerHTML = '';

    const activeTxns = issuedBooks.filter(i => i.status === 'Active');
    if (activeTxns.length === 0) {
        tbody.innerHTML = `<tr><td colspan="5" class="p-6 text-center text-slate-400">No active book loans currently.</td></tr>`;
        return;
    }

    activeTxns.forEach(i => {
        const fine = calculateFine(i.dueDate);
        const fineBadge = fine > 0 
            ? `<span class="bg-rose-100 text-rose-700 font-bold px-2.5 py-1 rounded-full text-xs">Overdue Fine: ₹${fine}</span>` 
            : `<span class="bg-emerald-100 text-emerald-700 font-bold px-2.5 py-1 rounded-full text-xs">On Time</span>`;

        tbody.innerHTML += `
            <tr class="hover:bg-slate-50 transition">
                <td class="p-4 font-mono font-semibold text-amber-600">${i.txnId}</td>
                <td class="p-4">
                    <p class="font-bold text-slate-900">${i.bookTitle}</p>
                    <p class="text-xs text-slate-500">Borrower: ${i.memberName}</p>
                </td>
                <td class="p-4 text-slate-600">${i.dueDate}</td>
                <td class="p-4">${fineBadge}</td>
                <td class="p-4 text-right">
                    <button onclick="returnBook('${i.txnId}')" class="bg-emerald-600 hover:bg-emerald-700 text-white px-4 py-2 rounded-xl text-xs font-semibold shadow transition">Return Book</button>
                </td>
            </tr>
        `;
    });
}

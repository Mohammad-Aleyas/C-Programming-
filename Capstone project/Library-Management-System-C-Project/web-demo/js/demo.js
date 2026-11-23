const books = [
    { id: 'B101', title: 'C Programming Language', author: 'Dennis Ritchie', category: 'Computer Science', qty: 5, available: 4 },
    { id: 'B102', title: 'Data Structures & Algorithms', author: 'Mark Allen', category: 'Computer Science', qty: 4, available: 4 },
    { id: 'B103', title: 'Engineering Mathematics', author: 'B.S. Grewal', category: 'Mathematics', qty: 6, available: 6 },
    { id: 'B104', title: 'Digital Logic Design', author: 'Morris Mano', category: 'Electronics', qty: 3, available: 2 }
];
window.onload = () => {
    document.getElementById('stat-books').innerText = books.reduce((s, b) => s + b.qty, 0);
    document.getElementById('stat-members').innerText = 3;
    document.getElementById('stat-issued').innerText = 2;
    document.getElementById('stat-fines').innerText = '₹30';
    const tbody = document.getElementById('books-table-body');
    books.forEach(b => {
        tbody.innerHTML += `<tr><td class="p-3 font-mono text-blue-600 font-bold">${b.id}</td><td class="p-3"><b>${b.title}</b><br><span class="text-xs text-slate-500">${b.author}</span></td><td class="p-3">${b.category}</td><td class="p-3">${b.qty}</td><td class="p-3 text-emerald-600 font-bold">${b.available}</td></tr>`;
    });
};

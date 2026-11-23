// MODULE 4: AUDIT REPORTS & FINE SUMMARY
function renderReports() {
    const tbody = document.getElementById('reports-table-body');
    tbody.innerHTML = '';

    if (issuedBooks.length === 0) {
        tbody.innerHTML = `<tr><td colspan="6" class="p-6 text-center text-slate-400">No transaction logs available.</td></tr>`;
        return;
    }

    issuedBooks.forEach(i => {
        const fine = i.status === 'Active' ? calculateFine(i.dueDate) : 0;
        const statusBadge = i.status === 'Active'
            ? (fine > 0 ? `<span class="text-rose-600 font-bold">Overdue (₹${fine})</span>` : `<span class="text-amber-600 font-semibold">Active Loan</span>`)
            : `<span class="text-emerald-600 font-semibold">Returned</span>`;

        tbody.innerHTML += `
            <tr class="hover:bg-slate-50 transition">
                <td class="p-4 font-mono text-xs">${i.txnId}</td>
                <td class="p-4 font-bold text-slate-900">${i.bookTitle}</td>
                <td class="p-4 text-slate-700">${i.memberName}</td>
                <td class="p-4 text-slate-600">${i.issueDate}</td>
                <td class="p-4 text-slate-600">${i.dueDate}</td>
                <td class="p-4">${statusBadge}</td>
            </tr>
        `;
    });
}

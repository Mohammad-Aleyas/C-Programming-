// MAIN APPLICATION CONTROLLER, NAVIGATION & DASHBOARD METRICS
function showToast(title, message, isError = false) {
    const toast = document.getElementById('toast');
    const icon = document.getElementById('toast-icon');
    document.getElementById('toast-title').innerText = title;
    document.getElementById('toast-message').innerText = message;
    
    if (isError) {
        icon.className = 'fa-solid fa-circle-exclamation text-rose-400 text-xl';
    } else {
        icon.className = 'fa-solid fa-circle-check text-emerald-400 text-xl';
    }

    toast.classList.remove('translate-x-full');
    setTimeout(() => {
        toast.classList.add('translate-x-full');
    }, 3500);
}

function switchTab(tabId) {
    document.querySelectorAll('.tab-content').forEach(el => el.classList.add('hidden'));
    document.getElementById(`content-${tabId}`).classList.remove('hidden');

    ['books', 'members', 'circulation', 'reports'].forEach(t => {
        const btn = document.getElementById(`tab-${t}`);
        if (t === tabId) {
            btn.className = 'flex-1 min-w-[140px] py-3 px-4 rounded-xl font-semibold text-sm transition flex items-center justify-center gap-2 bg-blue-600 text-white shadow-md shadow-blue-500/20';
        } else {
            btn.className = 'flex-1 min-w-[140px] py-3 px-4 rounded-xl font-semibold text-sm transition flex items-center justify-center gap-2 text-slate-600 hover:bg-slate-100';
        }
    });

    if (tabId === 'circulation') {
        populateIssueDropdowns();
    }
    if (tabId === 'reports') {
        document.getElementById('print-date').innerText = new Date().toLocaleDateString();
    }
}

function openModal(id) {
    document.getElementById(id).classList.remove('hidden');
}

function closeModal(id) {
    document.getElementById(id).classList.add('hidden');
}

function updateStatistics() {
    document.getElementById('stat-books').innerText = books.reduce((sum, b) => sum + parseInt(b.qty), 0);
    document.getElementById('stat-members').innerText = members.length;
    document.getElementById('stat-issued').innerText = issuedBooks.filter(i => i.status === 'Active').length;

    let totalFines = 0;
    issuedBooks.forEach(i => {
        if (i.status === 'Active') {
            totalFines += calculateFine(i.dueDate);
        }
    });
    document.getElementById('stat-fines').innerText = `₹${totalFines}`;
    document.getElementById('report-total-books').innerText = books.reduce((sum, b) => sum + parseInt(b.qty), 0);
    document.getElementById('report-total-members').innerText = members.length;
    document.getElementById('report-total-fines').innerText = `₹${totalFines}`;

    renderBooks();
    renderMembers();
    renderIssuedBooks();
    renderReports();
}

window.onload = function() {
    updateStatistics();
};

// Initial Sample Data & Browser LocalStorage Persistence
const defaultBooks = [
    { id: 'B101', title: 'C Programming Language', author: 'Dennis Ritchie', category: 'Computer Science', qty: 5, available: 3 },
    { id: 'B102', title: 'Data Structures & Algorithms', author: 'Mark Allen', category: 'Computer Science', qty: 4, available: 4 },
    { id: 'B103', title: 'Engineering Mathematics', author: 'B.S. Grewal', category: 'Mathematics', qty: 6, available: 5 },
    { id: 'B104', title: 'Digital Logic Design', author: 'Morris Mano', category: 'Electronics', qty: 3, available: 2 }
];

const defaultMembers = [
    { id: 'M201', name: 'Mohammad Aleyas', dept: 'Computer Science & Engineering', contact: '+91 9876543210' },
    { id: 'M202', name: 'K. Santhosh Kumar', dept: 'Information Technology', contact: '+91 9123456789' },
    { id: 'M203', name: 'B. Mahesh Kumar', dept: 'Electronics & Communication', contact: '+91 9988776655' }
];

const defaultIssued = [
    { txnId: 'TXN-901', bookId: 'B101', bookTitle: 'C Programming Language', memberId: 'M202', memberName: 'K. Santhosh Kumar', issueDate: '2026-11-01', dueDate: '2026-11-15', status: 'Active' },
    { txnId: 'TXN-902', bookId: 'B104', bookTitle: 'Digital Logic Design', memberId: 'M203', memberName: 'B. Mahesh Kumar', issueDate: '2026-11-10', dueDate: '2026-11-24', status: 'Active' }
];

let books = JSON.parse(localStorage.getItem('lms_books')) || defaultBooks;
let members = JSON.parse(localStorage.getItem('lms_members')) || defaultMembers;
let issuedBooks = JSON.parse(localStorage.getItem('lms_issued')) || defaultIssued;

function saveData() {
    localStorage.setItem('lms_books', JSON.stringify(books));
    localStorage.setItem('lms_members', JSON.stringify(members));
    localStorage.setItem('lms_issued', JSON.stringify(issuedBooks));
    updateStatistics();
}

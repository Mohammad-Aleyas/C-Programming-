// MODULE 2: LIBRARY MEMBER DIRECTORY
function openMemberModal(isEdit = false, memberId = null) {
    const form = document.getElementById('memberForm');
    form.reset();
    if (isEdit && memberId) {
        const m = members.find(item => item.id === memberId);
        document.getElementById('memberModalTitle').innerText = 'Edit Member Profile';
        document.getElementById('member-edit-id').value = m.id;
        document.getElementById('member-id').value = m.id;
        document.getElementById('member-id').disabled = true;
        document.getElementById('member-name').value = m.name;
        document.getElementById('member-dept').value = m.dept;
        document.getElementById('member-contact').value = m.contact;
    } else {
        document.getElementById('memberModalTitle').innerText = 'Register Member';
        document.getElementById('member-edit-id').value = '';
        document.getElementById('member-id').disabled = false;
    }
    openModal('memberModal');
}

function handleSaveMember(e) {
    e.preventDefault();
    const editId = document.getElementById('member-edit-id').value;
    const id = document.getElementById('member-id').value.trim();
    const name = document.getElementById('member-name').value.trim();
    const dept = document.getElementById('member-dept').value;
    const contact = document.getElementById('member-contact').value.trim();

    if (editId) {
        const m = members.find(item => item.id === editId);
        m.name = name;
        m.dept = dept;
        m.contact = contact;
        showToast('Member Updated', `Successfully updated profile for ${name}.`);
    } else {
        if (members.some(item => item.id === id)) {
            showToast('Error', `Member ID "${id}" already exists!`, true);
            return;
        }
        members.push({ id, name, dept, contact });
        showToast('Member Registered', `Successfully registered ${name}.`);
    }

    saveData();
    closeModal('memberModal');
}

function deleteMember(id) {
    if (confirm('Are you sure you want to remove this member?')) {
        members = members.filter(m => m.id !== id);
        saveData();
        showToast('Member Removed', 'Member directory updated.');
    }
}

function renderMembers() {
    const query = document.getElementById('search-member-input').value.toLowerCase();
    const tbody = document.getElementById('members-table-body');
    tbody.innerHTML = '';

    const filtered = members.filter(m => m.name.toLowerCase().includes(query) || m.id.toLowerCase().includes(query) || m.dept.toLowerCase().includes(query));

    if (filtered.length === 0) {
        tbody.innerHTML = `<tr><td colspan="5" class="p-6 text-center text-slate-400">No registered members found.</td></tr>`;
        return;
    }

    filtered.forEach(m => {
        tbody.innerHTML += `
            <tr class="hover:bg-slate-50 transition">
                <td class="p-4 font-mono font-semibold text-blue-600">${m.id}</td>
                <td class="p-4 font-bold text-slate-900">${m.name}</td>
                <td class="p-4 text-slate-600">${m.dept}</td>
                <td class="p-4 text-slate-600">${m.contact}</td>
                <td class="p-4 text-right space-x-2 no-print">
                    <button onclick="openMemberModal(true, '${m.id}')" class="text-blue-600 hover:text-blue-800 p-1.5"><i class="fa-solid fa-pen"></i></button>
                    <button onclick="deleteMember('${m.id}')" class="text-rose-600 hover:text-rose-800 p-1.5"><i class="fa-solid fa-trash"></i></button>
                </td>
            </tr>
        `;
    });
}

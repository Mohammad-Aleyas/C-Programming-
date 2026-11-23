#include <stdio.h>
#include <string.h>
#include "library.h"

extern Member members[MAX_MEMBERS];
extern int member_count;

void registerMember(void) {
    if (member_count >= MAX_MEMBERS) {
        printf("[Error] Member directory is full.\n");
        return;
    }

    Member m;
    printf("Enter Member ID / Roll No (e.g., M204): ");
    scanf("%19s", m.id);
    clearInputBuffer();

    if (findMemberIndex(m.id) != -1) {
        printf("[Error] Member ID '%s' already exists!\n", m.id);
        return;
    }

    printf("Enter Full Name: ");
    fgets(m.name, sizeof(m.name), stdin);
    m.name[strcspn(m.name, "\n")] = '\0';

    printf("Enter Department: ");
    fgets(m.department, sizeof(m.department), stdin);
    m.department[strcspn(m.department, "\n")] = '\0';

    printf("Enter Contact Phone No: ");
    fgets(m.contact, sizeof(m.contact), stdin);
    m.contact[strcspn(m.contact, "\n")] = '\0';

    members[member_count++] = m;
    saveAllData();
    printf("[Success] Registered member '%s' (%s).\n", m.name, m.id);
}

void displayMembers(void) {
    if (member_count == 0) {
        printf("No registered members found.\n");
        return;
    }

    printf("\n%-10s | %-24s | %-30s | %-16s\n",
           "Member ID", "Full Name", "Department", "Contact No");
    printf("----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < member_count; i++) {
        printf("%-10s | %-24s | %-30s | %-16s\n",
               members[i].id, members[i].name,
               members[i].department, members[i].contact);
    }
}

void editMember(void) {
    char id[20];
    printf("Enter Member ID to edit: ");
    scanf("%19s", id);
    clearInputBuffer();

    int idx = findMemberIndex(id);
    if (idx == -1) {
        printf("[Error] Member ID '%s' not found.\n", id);
        return;
    }

    Member *m = &members[idx];
    printf("Editing '%s' (%s)\n", m->name, m->department);

    printf("Enter New Full Name: ");
    fgets(m->name, sizeof(m->name), stdin);
    m->name[strcspn(m->name, "\n")] = '\0';

    printf("Enter New Department: ");
    fgets(m->department, sizeof(m->department), stdin);
    m->department[strcspn(m->department, "\n")] = '\0';

    printf("Enter New Contact Phone No: ");
    fgets(m->contact, sizeof(m->contact), stdin);
    m->contact[strcspn(m->contact, "\n")] = '\0';

    saveAllData();
    printf("[Success] Member '%s' updated.\n", m->id);
}

void deleteMember(void) {
    char id[20];
    printf("Enter Member ID to remove: ");
    scanf("%19s", id);

    int idx = findMemberIndex(id);
    if (idx == -1) {
        printf("[Error] Member ID '%s' not found.\n", id);
        return;
    }

    for (int i = idx; i < member_count - 1; i++) {
        members[i] = members[i + 1];
    }
    member_count--;
    saveAllData();
    printf("[Success] Member '%s' removed from directory.\n", id);
}

void searchMember(void) {
    char query[80];
    clearInputBuffer();
    printf("Search Member by ID, Name, or Department: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < member_count; i++) {
        if (strcmp(members[i].id, query) == 0 ||
            strstr(members[i].name, query) != NULL ||
            strstr(members[i].department, query) != NULL) {
            printf(" -> [%s] %s | %s | %s\n",
                   members[i].id, members[i].name,
                   members[i].department, members[i].contact);
            found = 1;
        }
    }
    if (!found) {
        printf("No matching member found.\n");
    }
}

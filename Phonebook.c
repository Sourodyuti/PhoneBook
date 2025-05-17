#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTACTS 100
#define MAX_NAME 50

typedef struct {
    char name[MAX_NAME];
    long number;
} Contact;

Contact phonebook[MAX_CONTACTS];
int contactCount = 0;

// Merge sort helpers
void merge(Contact arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Contact L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcasecmp(L[i].name, R[j].name) <= 0)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(Contact arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Add contact
void addContact(const char *name, long number) {
    if (contactCount >= MAX_CONTACTS) {
        printf("Phonebook full\n");
        return;
    }
    strncpy(phonebook[contactCount].name, name, MAX_NAME - 1);
    phonebook[contactCount].name[MAX_NAME - 1] = '\0';
    phonebook[contactCount].number = number;
    contactCount++;
    mergeSort(phonebook, 0, contactCount - 1);
    printf("Contact added\n");
}

// Search contact by name
void searchByName(const char *name) {
    for (int i = 0; i < contactCount; i++) {
        if (strcasecmp(phonebook[i].name, name) == 0) {
            printf("Name: %s\nNumber: %ld\n", phonebook[i].name, phonebook[i].number);
            return;
        }
    }
    printf("Contact not found\n");
}

// Search contact by number
void searchByNumber(long number) {
    for (int i = 0; i < contactCount; i++) {
        if (phonebook[i].number == number) {
            printf("Name: %s\nNumber: %ld\n", phonebook[i].name, phonebook[i].number);
            return;
        }
    }
    printf("Contact not found\n");
}

// View all contacts
void viewAllContacts() {
    if (contactCount == 0) {
        printf("No contacts to display\n");
        return;
    }
    printf("\n--- Contact List ---\n");
    for (int i = 0; i < contactCount; i++) {
        printf("%s - %ld\n", phonebook[i].name, phonebook[i].number);
    }
}

// Delete contact by name
void deleteByName(const char *name) {
    int found = 0;
    for (int i = 0; i < contactCount; i++) {
        if (strcasecmp(phonebook[i].name, name) == 0) {
            found = 1;
            // Shift all elements after this one left by one position
            for (int j = i; j < contactCount - 1; j++) {
                phonebook[j] = phonebook[j + 1];
            }
            contactCount--;
            printf("Contact deleted successfully\n");
            break;
        }
    }
    if (!found) {
        printf("Contact not found\n");
    }
}

// Delete contact by number
void deleteByNumber(long number) {
    int found = 0;
    for (int i = 0; i < contactCount; i++) {
        if (phonebook[i].number == number) {
            found = 1;
            // Shift all elements after this one left by one position
            for (int j = i; j < contactCount - 1; j++) {
                phonebook[j] = phonebook[j + 1];
            }
            contactCount--;
            printf("Contact deleted successfully\n");
            break;
        }
    }
    if (!found) {
        printf("Contact not found\n");
    }
}

int main() {
    int choice;
    char name[MAX_NAME];
    long number;

    while (1) {
        printf("\n1. Add Contact\n2. Search by Name\n3. Search by Number\n");
        printf("4. View All\n5. Delete by Name\n6. Delete by Number\n7. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        while (getchar() != '\n'); // clear leftover newline

        if (choice == 1) {
            printf("Enter name: ");
            fgets(name, MAX_NAME, stdin);
            name[strcspn(name, "\n")] = '\0';

            printf("Enter number: ");
            if (scanf("%ld", &number) != 1) {
                printf("Invalid number.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
            addContact(name, number);

        } else if (choice == 2) {
            printf("Enter name to search: ");
            fgets(name, MAX_NAME, stdin);
            name[strcspn(name, "\n")] = '\0';
            searchByName(name);

        } else if (choice == 3) {
            printf("Enter number to search: ");
            if (scanf("%ld", &number) != 1) {
                printf("Invalid number.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
            searchByNumber(number);

        } else if (choice == 4) {
            viewAllContacts();

        } else if (choice == 5) {
            printf("Enter name to delete: ");
            fgets(name, MAX_NAME, stdin);
            name[strcspn(name, "\n")] = '\0';
            deleteByName(name);

        } else if (choice == 6) {
            printf("Enter number to delete: ");
            if (scanf("%ld", &number) != 1) {
                printf("Invalid number.\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
            deleteByNumber(number);

        } else if (choice == 7) {
            printf("Exiting...\n");
            break;

        } else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}

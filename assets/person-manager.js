class PersonManager {
  constructor(people) {
    this.people = JSON.parse(JSON.stringify(people)) || [];
    this.editingId = null;
    this.deleteId = null;
    this.init();
  }

  init() {
    this.bindEvents();
    this.renderTable();
    this.updateEmptyState();
  }

  bindEvents() {
    document
      .getElementById("personForm")
      .addEventListener("submit", (e) => this.handleSubmit(e));
    document
      .getElementById("cancelBtn")
      .addEventListener("click", () => this.cancelEdit());
    document
      .getElementById("searchInput")
      .addEventListener("input", (e) => this.handleSearch(e));
    document
      .getElementById("cancelDelete")
      .addEventListener("click", () => this.closeDeleteModal());
    document
      .getElementById("confirmDelete")
      .addEventListener("click", () => this.confirmDelete());

    document
      .getElementById("addPersonBtn")
      .addEventListener("click", () => this.openFormModal());
    document
      .getElementById("closeFormModal")
      .addEventListener("click", () => this.closeFormModal());

    // Close modals when clicking outside
    // document.getElementById('deleteModal').addEventListener('click', (e) => {
    //     if (e.target.id === 'deleteModal') {
    //         this.closeDeleteModal();
    //     }
    // });

    // document.getElementById('formModal').addEventListener('click', (e) => {
    //     if (e.target.id === 'formModal') {
    //         this.closeFormModal();
    //     }
    // });
  }

  openFormModal() {
    document.getElementById("formModal").style.display = "block";
  }

  closeFormModal() {
    document.getElementById("formModal").style.display = "none";
    this.resetForm();
  }

  async handleSubmit(e) {
    e.preventDefault();
    const formData = new FormData(e.target);
    const person = {
      name: formData.get("name").trim(),
      address: formData.get("address").trim(),
      age: parseInt(formData.get("age")),
    };

    if (this.editingId !== null) {
      await this.updatePerson(this.editingId, person);
    } else {
      this.addPerson(person);
    }

    this.closeFormModal();
    debugger;
    this.renderTable();
    this.updateEmptyState();
  }

  addPerson(person) {
    this.people.push(person);
    this.saveToStorage();
  }

  async updatePerson(id, updatedPerson) {
    const index = this.people.findIndex((p) => p.id === id);
    if (index !== -1) {
      document.getElementById("submitBtn").textContent = "Loading...";
      document.getElementById("submitBtn").disabled = true;
      const req = await fetch("/person", {
        method: "PUT",
        body: JSON.stringify({
          id: id,
          name: updatedPerson.name,
          address: updatedPerson.address,
          age: updatedPerson.age,
        }),
      });
      const res = await req.json();
      document.getElementById("submitBtn").disabled = false;
      document.getElementById("form-title").textContent = "Edit Person";

      this.people[index] = { ...updatedPerson, id };
    }
  }

  deletePerson(id) {
    this.people = this.people.filter((p) => p.id !== id);
    this.saveToStorage();
    this.renderTable();
    this.updateEmptyState();
  }

  editPerson(id) {
    const person = this.people.find((p) => p.id === id);
    if (person) {
      document.getElementById("name").value = person.name;
      document.getElementById("address").value = person.address;
      document.getElementById("age").value = person.age;
      document.getElementById("editId").value = id;

      this.editingId = id;
      document.getElementById("form-title").textContent = "Edit Person";
      document.getElementById("submitBtn").textContent = "Update Person";
      document.getElementById("cancelBtn").style.display = "block";

      this.openFormModal();
    }
  }

  cancelEdit() {
    this.closeFormModal();
  }

  resetForm() {
    document.getElementById("personForm").reset();
    document.getElementById("editId").value = "";
    this.editingId = null;
    document.getElementById("form-title").textContent = "Add New Person";
    document.getElementById("submitBtn").textContent = "Add Person";
    document.getElementById("cancelBtn").style.display = "none";
  }

  handleSearch(e) {
    const searchTerm = e.target.value.toLowerCase();
    const filteredPeople = this.people.filter(
      (person) =>
        person.name.toLowerCase().includes(searchTerm) ||
        person.address.toLowerCase().includes(searchTerm) ||
        person.age.toString().includes(searchTerm)
    );
    this.renderTable(filteredPeople);
  }

  showDeleteModal(id) {
    this.deleteId = id;
    document.getElementById("deleteModal").style.display = "block";
  }

  closeDeleteModal() {
    this.deleteId = null;
    document.getElementById("deleteModal").style.display = "none";
  }

  confirmDelete() {
    if (this.deleteId !== null) {
      this.deletePerson(this.deleteId);
      this.closeDeleteModal();
    }
  }

  renderTable(peopleToRender = this.people) {
    const tbody = document.getElementById("personTableBody");
    tbody.innerHTML = "";

    peopleToRender.forEach((person) => {
      const row = document.createElement("tr");
      row.innerHTML = `
                  <td>${this.escapeHtml(person.name)}</td>
                  <td>${this.escapeHtml(person.address)}</td>
                  <td>${person.age}</td>
                  <td>
                      <div class="action-buttons">
                          <button class="edit-btn" onclick="personManager.editPerson(${
                            person.id
                          })">Edit</button>
                          <button class="delete-btn" onclick="personManager.showDeleteModal(${
                            person.id
                          })">Delete</button>
                      </div>
                  </td>
              `;
      tbody.appendChild(row);
    });
  }

  updateEmptyState() {
    const emptyState = document.getElementById("emptyState");
    const tableContainer = document.querySelector(".table-container");

    if (this.people.length === 0) {
      emptyState.style.display = "block";
      tableContainer.style.display = "none";
    } else {
      emptyState.style.display = "none";
      tableContainer.style.display = "block";
    }
  }

  escapeHtml(text) {
    const div = document.createElement("div");
    div.textContent = text;
    return div.innerHTML;
  }

  saveToStorage() {
    localStorage.setItem("people", JSON.stringify(this.people));
  }
}

// Initialize the application
let personManager = [];
async function fetchData() {
  try {
    const response = await fetch("/person");
    const data = await response.json();
    personManager = new PersonManager(data.person);
  } catch (error) {
    console.error("Error fetching data:", error);
  }
}

fetchData();

const questions = JSON.parse(document.getElementById("questions").innerHTML);
document.getElementById("questions").remove();

const form = document.getElementById('quizForm');
const result = document.getElementById("result");

// Generate quiz questions
questions.forEach((q, index) => {
    const questionDiv = document.createElement("div");
    questionDiv.className = "question";
    questionDiv.innerHTML = `
        <h3>Question ${index + 1}:</h3>
        <p>${q.question}</p>
        <div class="options">
            ${q.options.map(option => `
                <div class="option">
                    <label>
                        <input type="radio" name=${index + 1} value="${option}">
                        ${option}
                    </label>
                </div>
            `).join("")}
        </div>`;
    form.insertAdjacentElement("beforeEnd", questionDiv);
});

// Calculate score
document.getElementById("submit").addEventListener("click", () => {
    const choices = [];

    for (let choice of document.querySelectorAll("input:checked")) {
        choices.push(choice.value);
    }

    fetch(document.location.href, {
        method: "POST",
        headers: {"Content-Type": "application/json"},
		body: JSON.stringify(choices)
    })
    .then(response => response.json())
    .then(grade => {
        result.style.display = "block";
        result.innerHTML = `
            <h2>Your Grade: ${grade.grade}</h2>
            <p>Result: ${grade.points / choices.length * 100}%</p>
        `;
    });
});
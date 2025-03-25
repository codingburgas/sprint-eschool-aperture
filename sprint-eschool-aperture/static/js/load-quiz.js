const questions = JSON.parse(document.getElementById("questions").innerHTML);

// Generate quiz questions
const form = document.getElementById('quizForm');
questions.forEach((q, index) => {
    const questionDiv = document.createElement('div');
    questionDiv.className = 'question';
    questionDiv.innerHTML = `
        <h3>Question ${index + 1}:</h3>
        <p>${q.question}</p>
        <div class="options">
            ${q.options.map((option, i) => `
                <div class="option">
                    <label>
                        <input type="radio" name="q${index}" value="${option}">
                        ${option}
                    </label>
                </div>
            `).join('')}
        </div>
    `;
    form.insertBefore(questionDiv, form.lastElementChild);
});

// Calculate score
function calculateScore() {
    let score = 0;
    questions.forEach((q, index) => {
        const selected = document.querySelector(`input[name="q${index}"]:checked`);
        if (selected && selected.value === q.answer) {
            score++;
        }
    });

    const percentage = (score / questions.length) * 100;
    const resultDiv = document.getElementById('result');
    resultDiv.style.display = 'block';
    resultDiv.innerHTML = `
        <h2>Your Score: ${score}/${questions.length}</h2>
        <p>Percentage: ${percentage.toFixed(1)}%</p>
        ${percentage >= 80 ? '🎉 Excellent work! 🎉' : 
         percentage >= 60 ? '👍 Good job! 👍' : 
         '💪 Keep practicing! 💪'}
    `;
}
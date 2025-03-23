// Quiz questions array
const questions = [
    {
        question: "What is the capital of France?",
        options: ["London", "Berlin", "Paris", "Madrid"],
        correct: 2
    },
    {
        question: "Which planet is known as the Red Planet?",
        options: ["Venus", "Mars", "Jupiter", "Saturn"],
        correct: 1
    },
    {
        question: "What is the largest mammal in the world?",
        options: ["African Elephant", "Blue Whale", "Giraffe", "Hippopotamus"],
        correct: 1
    },
    {
        question: "Who painted the Mona Lisa?",
        options: ["Vincent van Gogh", "Pablo Picasso", "Leonardo da Vinci", "Michelangelo"],
        correct: 2
    },
    {
        question: "What is the chemical symbol for gold?",
        options: ["Ag", "Fe", "Au", "Cu"],
        correct: 2
    },

    {
        question: "What is the longest river in the world?",
        options: ["Nile", "Amazon", "Yangtze", "Mississippi"],
        correct: 0
    },
    {
        question: "Which Shakespeare play features the characters Romeo and Juliet?",
        options: ["Hamlet", "Macbeth", "Romeo and Juliet", "Othello"],
        correct: 2
    },
    {
        question: "What is Newton's third law of motion?",
        options: [
            "An object at rest stays at rest",
            "Force equals mass times acceleration",
            "For every action there's an equal and opposite reaction",
            "Law of universal gravitation"
        ],
        correct: 2
    },
    {
        question: "What is the most abundant element in the Earth's atmosphere?",
        options: ["Oxygen", "Carbon", "Calcium", "Nitrogen"],
        correct: 3
    },
    {
        question: "Which planet in our solar system has the most moons?",
        options: ["Jupiter", "Saturn", "Neptune", "Earth"],
        correct: 0
    }
    
    // Add 10 more questions 
];

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
                        <input type="radio" name="q${index}" value="${i}">
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
        if (selected && parseInt(selected.value) === q.correct) {
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
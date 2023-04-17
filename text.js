const nameInput = document.getElementById('nameInput');
const idInput = document.getElementById('idInput');

document.querySelectorAll('input[name="choice"]').forEach((radio) => {
    radio.addEventListener('change', (event) => {
        if (event.target.value === 'name') {
            nameInput.style.display = 'block';
            idInput.style.display = 'none';
        } else if (event.target.value === 'id') {
            nameInput.style.display = 'none';
            idInput.style.display = 'block';
        }
    });
});

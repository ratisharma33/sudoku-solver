// app.js
// Wait for Emscripten Module to initialize
Module.onRuntimeInitialized = function() {
  // cwrap functions
  const set_cell = Module.cwrap('set_cell', 'null', ['number','number','number']);
  const get_cell = Module.cwrap('get_cell', 'number', ['number','number']);
  const solve = Module.cwrap('solve', 'number', []);
  const reset_board = Module.cwrap('reset_board', 'null', []);
  const load_default = Module.cwrap('load_default', 'null', []);

  const gridEl = document.getElementById('grid');
  const statusEl = document.getElementById('status');

  // create 9x9 inputs
  const inputs = [];
  for (let r = 0; r < 9; r++) {
    inputs[r] = [];
    for (let c = 0; c < 9; c++) {
      const inp = document.createElement('input');
      inp.type = 'text';
      inp.maxLength = 1;
      inp.dataset.r = r;
      inp.dataset.c = c;
      // only allow digits 1-9 or empty
      inp.addEventListener('input', (e) => {
        const v = e.target.value.replace(/[^1-9]/g,'');
        e.target.value = v;
      });
      inputs[r][c] = inp;
      gridEl.appendChild(inp);
    }
  }

  function readGridToWasm() {
    for (let r = 0; r < 9; r++) {
      for (let c = 0; c < 9; c++) {
        const v = parseInt(inputs[r][c].value || '0', 10);
        set_cell(r, c, isNaN(v) ? 0 : v);
      }
    }
  }

  function readWasmToGrid() {
    for (let r = 0; r < 9; r++) {
      for (let c = 0; c < 9; c++) {
        const v = get_cell(r, c);
        inputs[r][c].value = v === 0 ? '' : String(v);
      }
    }
  }

  document.getElementById('loadBtn').addEventListener('click', () => {
    load_default();
    readWasmToGrid();
    statusEl.textContent = 'Loaded example.';
  });

  document.getElementById('resetBtn').addEventListener('click', () => {
    reset_board();
    for (let r=0;r<9;r++) for(let c=0;c<9;c++) inputs[r][c].value = '';
    statusEl.textContent = 'Cleared.';
  });

  document.getElementById('solveBtn').addEventListener('click', () => {
    statusEl.textContent = 'Solving...';
    readGridToWasm();
    // call solve
    const ok = solve();
    if (ok === 1) {
      readWasmToGrid();
      statusEl.textContent = 'Solved ✓';
    } else {
      statusEl.textContent = 'No solution found ✗';
    }
  });

  // initialize empty board
  reset_board();
};

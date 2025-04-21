const express = require('express'); //handles HTTP requests
const cors = require('cors'); //lets frontend ,local host:3000 "talk" to backend on a diff port ,5001
const {execFile} = require('child_process');
const path = require('path');

const app = express();
const PORT = 5001; // can use any port not in use

//middle-man stuff
app.use(cors()); //react app talking to server (cross-origin requests)
app.use(express.json()); //parses JSON requests

//basic test route
app.post('/search', (req, res) => {
  const { actor1, actor2, algorithm } = req.body; //contains data frontend sends in JSON 
  console.log(`Searching from ${actor1} to ${actor2} using ${algorithm}`);

  // Validate input
  if (!actor1 || !actor2 || !algorithm) {
    return res.status(400).json({ error: 'Missing input fields.' });
  }

  //route to run c++ binary oooouuu
  const binaryPath = path.join(__dirname, "../CLion/Datasets/Project3");

  //args passed to the c++ binary
  const args = [actor1, actor2, algorithm];

  //run binary & send its output back to the frontend //changed working directory because it was giving many issues b/w CLion and VS code 
  execFile(binaryPath, args, { cwd: path.join(__dirname, "../CLion") }, (error, stdout, stderr) => {
    if (error) {
      console.error("Error running C++ binary:", error.message);
      return res.status(500).json({ result: "Backend error!" });
    }

    console.log("C++ output:", stdout);
    return res.json({ result: stdout });
  });
});

// Start server
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);

});

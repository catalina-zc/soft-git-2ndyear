import subprocess

# Define the command and arguments inside a list
command = ['./myvicsek', '0.14']

# Call the C++ program via subprocess
result = subprocess.run(command, capture_output=True, text=True)

# Print the output
print("Standard Output:", result.stdout)
print("Standard Error:", result.stderr)
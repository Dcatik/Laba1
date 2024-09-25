import numpy as np

# Function to create random matrices and save them in the specified format
def create_matrices():
    for size in range(5, 26, 5):  # From 5x5 to 25x25 in increments of 5
        for i in range(1, 11):  # Create 10 matrices for each size
            # Generate a random matrix with values between -20 and 20
            matrix = np.random.randint(-20, 21, size=(size, size))
            # Define the filename
            file_name = f"matrix_{size}x{size}_{i}.txt"
            # Save the matrix to a text file in the required format
            with open(file_name, 'w') as f:
                f.write(f"{size} {size}\n")  # First line with dimensions
                for row in matrix:
                    f.write(" ".join(map(str, row)) + "\n")  # Write each row

# Call the function to create matrices
create_matrices()

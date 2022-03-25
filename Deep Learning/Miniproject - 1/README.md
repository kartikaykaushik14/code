Steps to run the code - 
1. Login to NYU HPC Greene.
3. Upload the project1_model.py and run.SBATCH on the desired location.
4. Modify the run.SBATCH file to point to the location of the source file and modify the path in --overlay
5. Run the batch file with the command: sbatch run.SBATCH
6. The output file would be present under the name - output.out and the .pt file would be saved as project1_model.pt in the same directory.

In order to load the project1_model.pt file, run the following command in a .py file - torch.load(project1_model.pt)

Steps to run the code - 
1. Login to NYU HPC Greene.
3. Upload the project1_model.py, project1_model.pt and run.SBATCH on the desired location.
4. Modify the run.SBATCH file to point to the location of the self_eval.py file and modify the path in --overlay
5. Run the batch file with the command: sbatch run.SBATCH
6. The output file would be present under the name - output.out in the same directory.

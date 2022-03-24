#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=16
#SBATCH --time=6:00:00
#SBATCH --mem=64GB
#SBATCH --gres=gpu:rtx8000
#SBATCH --job-name=output
#SBATCH --output=%x.out

module purge


singularity exec --nv \
            --overlay /scratch/kk4332/pytorch-example/my_pytorch.ext3:ro \
            /scratch/work/public/singularity/cuda11.2.2-cudnn8-devel-ubuntu20.04.sif \
            /bin/bash -c "source /ext3/env.sh; python Master_File.py"

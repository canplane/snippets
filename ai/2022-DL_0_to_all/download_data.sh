#!/usr/bin/env bash
# Fetches the MNIST and CIFAR-10 datasets used by these notebooks into
# MNIST_data/ and cifar10/, matching the paths passed to
# torchvision.datasets.MNIST/CIFAR10(..., download=True) inline.
set -e
python3 -c "
import torchvision.datasets as dsets
dsets.MNIST(root='MNIST_data/', train=True, download=True)
dsets.MNIST(root='MNIST_data/', train=False, download=True)
dsets.CIFAR10(root='cifar10/', train=True, download=True)
dsets.CIFAR10(root='cifar10/', train=False, download=True)
"

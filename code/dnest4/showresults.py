from corner import corner
import numpy as np

sample = np.loadtxt("sample.txt")
sample_info = np.loadtxt("sample_info.txt")

# Take samples from highest level
sample = sample[sample_info[:,0] == 14, :]
sample = np.vstack([sample[:,0], np.exp(sample[:,1])**2]).T
print(sample.shape)
fig = corner(sample, bins=128, labels = ["mean", "var"])
print("saving corner plot...")
fig.savefig("corner.png", bbox_inches="tight")


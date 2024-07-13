from sklearn.metrics import entropy

data = [1, 2, 3, 4]
prob_data = np.array(data) / np.sum(data)
ent = entropy(prob_data)
print(ent)
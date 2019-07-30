import random
from builtins import range
import copy

POP_SIZE = 40   # Tamanho da população ∈ [50 ; 100]
GEN_MAX = 500   # Quantidade máxima de gerações.
RHO_C = 0.8     # Taxa de cruzamento ∈ [0,5 ; 1,0]
RHO_M = 0.01    # Taxa de mutação ∈ [0,001 ; 0,01]

OPTIMUM = 0
N = 0
CAPACITY = 0
profit = []
weight = []
population = []
parents = []
children = []


class Chromosome:

    def __init__(self, configuration, fitness_value, total_weight):
        self.configuration = configuration
        self.fitness_value = fitness_value
        self.total_weight = total_weight

    @property
    def configuration(self):
        return self._configuration

    @property
    def fitness_value(self):
        return self._fitness_value

    @property
    def total_weight(self):
        return self._total_weight

    @configuration.setter
    def configuration(self, configuration):
        self._configuration = configuration

    @fitness_value.setter
    def fitness_value(self, fitness_value):
        self._fitness_value = fitness_value

    @total_weight.setter
    def total_weight(self, total_weight):
        self._total_weight = total_weight

    def __repr__(self):
        return str(self.configuration) + " (" + str(self.fitness_value) + ") (" + str(self.total_weight) + ")"


best_solution = Chromosome([], 0.0, 0.0)


def read_data():

    file = open("Casos de testes/large_scale/knapPI_1_100_1000_1", "r")
    file_2 = open("Casos de testes/large_scale-optimum/knapPI_1_100_1000_1", "r")

    global OPTIMUM
    global N
    global CAPACITY
    line = file.readline().split()
    N = int(line[0])
    CAPACITY = int(line[1])
    OPTIMUM = float(file_2.readline())
    for line in file:
        data = line.split()
        profit.append(float(data[0]))
        weight.append(float(data[1]))

    file.close()
    file_2.close()


def initial_population():

    configuration = []
    for i in range(POP_SIZE):
        for j in range(N):
            configuration.append(random.randint(0, 1))

        chromosome = Chromosome(configuration.copy(), compute_fitness(configuration), compute_weight(configuration))
        if i == 0 or chromosome.fitness_value < population[-1].fitness_value:
            population.append(chromosome)
        else:
            pos = 0
            while pos < len(population):
                if chromosome.fitness_value >= population[pos].fitness_value:
                    population.insert(pos, chromosome)
                    break
                pos += 1

        configuration.clear()


def compute_weight(configuration):

    sum_weight = 0
    for i in range(N):
        sum_weight += weight[i] * configuration[i]

    return sum_weight


def compute_fitness(configuration):

    fit = 0
    for i in range(N):
        fit += profit[i] * configuration[i]

    return fit


def selection():

    # Seleção por torneio
    k = 5   # k ∈ {2,...,POP_SIZE}
    competitors = []
    for i in range(2):
        while len(competitors) < k:
            j = random.randint(0, POP_SIZE - 1)
            competitors.append(j)

        bigger_fitness = 0
        winner_pos = 0
        for l in range(k):
            if population[competitors[l]].fitness_value > bigger_fitness:
                bigger_fitness = population[competitors[l]].fitness_value
                winner_pos = competitors[l]

        parents.append(copy.deepcopy(population[winner_pos]))
        competitors.clear()


def crossover():

    p = random.uniform(0.0, 1.0)  # Gera um número aleatório no intervalo [0.0, 1.0]

    if p < RHO_C:
        # Cruzamento de um ponto
        point = random.randint(0, N - 1)  # Ponto de recombinação
        configuration1 = parents[0].configuration[0:point]
        configuration2 = parents[1].configuration[0:point]
        configuration1.extend(parents[1].configuration[point:N])
        configuration2.extend(parents[0].configuration[point:N])

        chromosome1 = Chromosome(configuration1, compute_fitness(configuration1), compute_weight(configuration1))
        chromosome2 = Chromosome(configuration2, compute_fitness(configuration2), compute_weight(configuration2))

        children.append(chromosome1)
        children.append(chromosome2)
    else:
        children.append(copy.deepcopy(parents[0]))
        children.append(copy.deepcopy(parents[1]))


def mutation():

    for i in range(2):
        check = False
        for j in range(N):
            p = random.uniform(0.0, 1.0)
            if p < RHO_M:
                check = True
                pos = random.randint(0, N - 1)
                if children[i].configuration[pos] == 0:
                    children[i].configuration[pos] = 1
                else:
                    children[i].configuration[pos] = 0

        if check:
            children[i].fitness_value = compute_fitness(children[i].configuration)
            children[i].total_weight = compute_weight(children[i].configuration)

    transform()

    # Insere filhos na população.
    for i in range(2):
        if children[i].fitness_value < population[-1].fitness_value:
            population.append(children[i])
        else:
            pos = 0
            while pos < len(population):
                if children[i].fitness_value >= population[pos].fitness_value:
                    population.insert(pos, children[i])    # OBS
                    break
                pos += 1

    parents.clear()
    children.clear()


def transform():

    for i in range(len(children)):
        while children[i].total_weight > CAPACITY:
            smaller = 1000000000000000000000000.0
            for j in range(N):
                if children[i].configuration[j] == 1:
                    if profit[j] / weight[j] < smaller:
                        smaller = profit[j] / weight[j]
                        index = j

            children[i].configuration[index] = 0
            children[i].fitness_value = compute_fitness(children[i].configuration)
            children[i].total_weight = compute_weight(children[i].configuration)


def elitism():

    evaluate_best_solution()

    while len(population) != POP_SIZE:
        population.pop()


def evaluate_best_solution():

    global best_solution
    for chromosome in population:
        if chromosome.total_weight <= CAPACITY and chromosome.fitness_value >= best_solution.fitness_value:
            if chromosome.fitness_value == best_solution.fitness_value and chromosome.total_weight < best_solution.total_weight:
                best_solution = copy.deepcopy(chromosome)
            elif chromosome.fitness_value > best_solution.fitness_value:
                best_solution = copy.deepcopy(chromosome)


def genetic_algorithm():

    read_data()
    initial_population()
    evaluate_best_solution()

    i = 0
    while best_solution.fitness_value != OPTIMUM and i < GEN_MAX:

        for j in range(POP_SIZE//2):
            selection()
            crossover()
            mutation()
            elitism()

        i += 1

    print("Amount of generations: {}".format(i))
    print("\nInput:\n\nN = {} C = {} OPTIMUM = {} \nP = {}\nA = {}".format(N, CAPACITY, OPTIMUM, profit, weight))
    print("\nOutput: {}\nFitness: {}\nRecurso usado: {}\n".format(best_solution.configuration, best_solution.fitness_value, best_solution.total_weight))


genetic_algorithm()

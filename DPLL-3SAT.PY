{
  "nbformat": 4,
  "nbformat_minor": 0,
  "metadata": {
    "colab": {
      "provenance": [],
      "authorship_tag": "ABX9TyMttfvLb+61+WWXXfOPoZQO",
      "include_colab_link": true
    },
    "kernelspec": {
      "name": "python3",
      "display_name": "Python 3"
    },
    "language_info": {
      "name": "python"
    }
  },
  "cells": [
    {
      "cell_type": "markdown",
      "metadata": {
        "id": "view-in-github",
        "colab_type": "text"
      },
      "source": [
        "<a href=\"https://colab.research.google.com/github/sebastianatanasovici-wq/3-SAT/blob/main/DPLL-3SAT.PY\" target=\"_parent\"><img src=\"https://colab.research.google.com/assets/colab-badge.svg\" alt=\"Open In Colab\"/></a>"
      ]
    },
    {
      "cell_type": "code",
      "execution_count": 1,
      "metadata": {
        "colab": {
          "base_uri": "https://localhost:8080/"
        },
        "id": "CxD4xHF5V3im",
        "outputId": "97574d92-b748-425c-8762-a99c4fd79206"
      },
      "outputs": [
        {
          "output_type": "stream",
          "name": "stdout",
          "text": [
            "Solución encontrada:\n",
            "x1 = 0\n",
            "x2 = 0\n",
            "x3 = 0\n",
            "x4 = 0\n",
            "La fórmula es SATISFACIBLE\n",
            "Tiempo de ejecución: 0.00010037422180175781 segundos\n"
          ]
        }
      ],
      "source": [
        "import time\n",
        "\n",
        "def simplify(clauses, literal):\n",
        "    new_clauses = []\n",
        "    for clause in clauses:\n",
        "        if literal in clause:\n",
        "            continue\n",
        "        if -literal in clause:\n",
        "            new_clause = [x for x in clause if x != -literal]\n",
        "            if not new_clause:\n",
        "                return None\n",
        "            new_clauses.append(new_clause)\n",
        "        else:\n",
        "            new_clauses.append(clause)\n",
        "    return new_clauses\n",
        "\n",
        "def unit_propagation(clauses):\n",
        "    assignment = {}\n",
        "    while True:\n",
        "        unit = None\n",
        "        for clause in clauses:\n",
        "            if len(clause) == 1:\n",
        "                unit = clause[0]\n",
        "                break\n",
        "        if unit is None:\n",
        "            break\n",
        "        clauses = simplify(clauses, unit)\n",
        "        if clauses is None:\n",
        "            return None, None\n",
        "        assignment[abs(unit)] = unit > 0\n",
        "    return clauses, assignment\n",
        "\n",
        "def dpll(clauses, assignment):\n",
        "    clauses, unit_assign = unit_propagation(clauses)\n",
        "    if clauses is None:\n",
        "        return None\n",
        "    assignment.update(unit_assign)\n",
        "    if not clauses:\n",
        "        return assignment\n",
        "    literal = clauses[0][0]\n",
        "    result = dpll(simplify(clauses, literal), assignment.copy())\n",
        "    if result is not None:\n",
        "        return result\n",
        "    return dpll(simplify(clauses, -literal), assignment.copy())\n",
        "\n",
        "formula = [[1, -2, 3], [-1, 2, 4]]\n",
        "\n",
        "start = time.time()\n",
        "result = dpll(formula, {})\n",
        "end = time.time()\n",
        "\n",
        "n = 4\n",
        "\n",
        "if result is not None:\n",
        "    print(\"Solución encontrada:\")\n",
        "    for i in range(1, n + 1):\n",
        "        valor = result.get(i, False)\n",
        "        print(f\"x{i} = {1 if valor else 0}\")\n",
        "    print(\"La fórmula es SATISFACIBLE\")\n",
        "else:\n",
        "    print(\"No existe solución\")\n",
        "    print(\"La fórmula es INSATISFACIBLE\")\n",
        "\n",
        "print(f\"Tiempo de ejecución: {end - start} segundos\")"
      ]
    }
  ]
}
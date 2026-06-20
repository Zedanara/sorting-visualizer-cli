#pragma once
#include "sv/sorting/ISortAlgorithm.hpp"
#include <vector>

namespace sv::sorting {

    class QuickSort : public ISortAlgorithm {
    private:
        std::vector<int> m_data;
        std::vector<std::pair<int, int>> m_stack; // Zamiast rekurencji używamy stosu
        
        int m_comparisons = 0;
        int m_swaps = 0;
        bool m_finished = false;

        // Stan maszyny (State Machine) dla podziału (partitioning)
        enum State { POP_STACK, PARTITION_LOOP };
        State m_state = POP_STACK;
        
        int m_low = 0, m_high = 0;
        int m_pivot = 0, m_pivotIdx = 0;
        int m_i = 0, m_j = 0;

    public:
        void init(std::vector<int> data) override;
        bool step() override;
        
        const std::vector<int>& getData() const override;
        std::pair<int, int> getHighlightedIndices() const override;
        
        int getComparisonsCount() const override;
        int getSwapsCount() const override;
        std::string getName() const override;
        std::string getComplexityBest() const override;
        std::string getComplexityAverage() const override;
        std::string getComplexityWorst() const override;
        bool isFinished() const override;
    };

}
#pragma once
#include "sv/sorting/ISortAlgorithm.hpp"
#include <vector>

namespace sv::sorting {

    class HeapSort : public ISortAlgorithm {
    private:
        struct Frame {
            std::vector<int> data;
            std::pair<int, int> highlighted;
            int comps;
            int swaps;
        };

        std::vector<int> m_currentData;
        std::vector<Frame> m_frames;
        size_t m_currentFrame = 0;
        bool m_finished = false;

        void recordFrame(const std::vector<int>& arr, int h1, int h2, int comps, int swaps);
        void heapify(std::vector<int>& arr, int n, int i, int& comps, int& swaps);

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
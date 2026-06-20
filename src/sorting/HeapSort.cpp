#include "sv/sorting/HeapSort.hpp"
#include <algorithm>

namespace sv::sorting {

    void HeapSort::recordFrame(const std::vector<int>& arr, int h1, int h2, int comps, int swaps) {
        m_frames.push_back({arr, {h1, h2}, comps, swaps});
    }

    void HeapSort::heapify(std::vector<int>& arr, int n, int i, int& comps, int& swaps) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n) {
            comps++;
            if (arr[left] > arr[largest]) largest = left;
        }
        if (right < n) {
            comps++;
            if (arr[right] > arr[largest]) largest = right;
        }

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            swaps++;
            recordFrame(arr, i, largest, comps, swaps);
            heapify(arr, n, largest, comps, swaps);
        }
    }

    void HeapSort::init(std::vector<int> data) {
        m_frames.clear();
        m_currentFrame = 0;
        m_finished = (data.size() <= 1);
        m_currentData = data;
        
        int comps = 0;
        int swaps = 0;
        
        recordFrame(data, -1, -1, comps, swaps);
        
        std::vector<int> temp = data;
        int n = temp.size();

        // Budowanie kopca (Max Heap)
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(temp, n, i, comps, swaps);
        }

        // Ekstrakcja elementów z kopca
        for (int i = n - 1; i > 0; i--) {
            std::swap(temp[0], temp[i]);
            swaps++;
            recordFrame(temp, 0, i, comps, swaps);
            heapify(temp, i, 0, comps, swaps);
        }
        
        recordFrame(temp, -1, -1, comps, swaps);
    }

    bool HeapSort::step() {
        if (m_finished || m_frames.empty()) return false;
        if (m_currentFrame < m_frames.size() - 1) m_currentFrame++;
        else m_finished = true;
        return !m_finished;
    }

    const std::vector<int>& HeapSort::getData() const { return m_frames.empty() ? m_currentData : m_frames[m_currentFrame].data; }
    std::pair<int, int> HeapSort::getHighlightedIndices() const { return m_frames.empty() || m_finished ? std::pair<int,int>{-1, -1} : m_frames[m_currentFrame].highlighted; }
    int HeapSort::getComparisonsCount() const { return m_frames.empty() ? 0 : m_frames[m_currentFrame].comps; }
    int HeapSort::getSwapsCount() const { return m_frames.empty() ? 0 : m_frames[m_currentFrame].swaps; }
    std::string HeapSort::getName() const { return "Heap Sort"; }
    std::string HeapSort::getComplexityBest() const { return "O(n log n)"; }
    std::string HeapSort::getComplexityAverage() const { return "O(n log n)"; }
    std::string HeapSort::getComplexityWorst() const { return "O(n log n)"; }
    bool HeapSort::isFinished() const { return m_finished; }

}
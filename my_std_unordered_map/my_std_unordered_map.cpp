#include <iostream>
#include <utility>

namespace my_std {
    template<typename Key, typename Value>
    class Hashmap {
    private:
        using value_type = std::pair<const Key, Value>;

        struct Bucket {
            value_type data;
            Bucket* next;
            size_t hash_code;
        };
        Bucket** buckets;
        size_t hm_size;
        size_t hm_capacity;



        size_t hash_function(Key bucket_key) {
            std::hash<Key> hash;
            return hash(bucket_key) % hm_capacity;
        }



        void rehashing() {
            Bucket** old_buckets = buckets;
            size_t old_capacity = hm_capacity;

            hm_capacity *= 1.5;
            buckets = new Bucket * [hm_capacity]();

            for (size_t i = 0; i < old_capacity; i++) {
                Bucket* current = old_buckets[i];

                while (current != nullptr) {
                    Bucket* next_node = current->next;
                    current->next = nullptr;

                    size_t new_index = hash_function(current->data.first);
                    current->hash_code = new_index;

                    if (buckets[new_index] == nullptr) {
                        buckets[new_index] = current;
                    }
                    else {
                        Bucket* tail = buckets[new_index];
                        while (tail->next != nullptr) {
                            tail = tail->next;
                        }
                        tail->next = current;
                    }
                    current = next_node;
                }
            }
            delete[] old_buckets;
        }

        Bucket* check_dublication(const Key& arg_key) {
            Bucket* current = buckets[hash_function(arg_key)];
            while (current != nullptr) {
                if (current->data.first == arg_key) {
                    return current;
                }
                current = current->next;
            }
            return nullptr;
        }
    public:
        Hashmap() : hm_capacity(3), hm_size(0) {
            buckets = new Bucket * [hm_capacity]();
        }
        Hashmap(std::initializer_list<value_type> hm) : hm_capacity(3), hm_size(0) {
            buckets = new Bucket * [hm_capacity]();
            for (const auto& [key, value] : hm) {
                insert({ key, value });
            }
        }
        ~Hashmap() {
            Bucket* current_for_next = nullptr;
            for (int i = 0; i < hm_capacity; i++) {
                for (Bucket* current = buckets[i]; current != nullptr; current = current_for_next) {
                    current_for_next = current->next;
                    delete current;
                }
            }
            delete[] buckets;
            hm_capacity = 0;
            hm_size = 0;
        }

        void insert(const value_type& pair) {
            if (hm_capacity <= hm_size) {
                rehashing();
            }

            Bucket* dublicat = check_dublication(pair.first);
            if (dublicat != nullptr) {
                dublicat->data.second = pair.second;
            }
            else {
                size_t i = hash_function(pair.first);
                Bucket* newBucket = new Bucket{ pair, buckets[i], i };
                buckets[i] = newBucket;
                hm_size++;
            }
        }
        void remove(const Key& arg_key) {
            size_t index = hash_function(arg_key);
            Bucket* current = buckets[index];
            if (current == nullptr) {
                return;
            }

            if (current->data.first == arg_key) {
                buckets[index] = current->next;
                delete current;
                hm_size--;
            }
            else {
                while (current->next != nullptr) {
                    if (current->next->data.first == arg_key) {
                        Bucket* oldBucket = current->next;
                        current->next = oldBucket->next;
                        delete oldBucket;
                        hm_size--;
                        break;
                    }
                    current = current->next;
                }
            }
        }
        Bucket* search(const Key& arg_key) {
            Bucket* current = buckets[hash_function(arg_key)];
            while (current != nullptr) {
                if (current->data.first == arg_key) {
                    return current;
                }
                current = current->next;
            }
            return nullptr;
        }
    };



    template<typename Key, typename Value>
    class unordered_map {
    private:
        using value_type = std::pair<const Key, Value>;
        Hashmap<const Key, Value> hm;
    public:
        unordered_map(std::initializer_list<value_type> hm) {
            for (const auto& item : hm) {
                insert(item);
            }
        }

        void insert(const value_type& pair) {
            hm.insert(pair);
        }
        void erase(const Key& pair) {
            hm.remove(pair);
        }
    };

};


int main()
{
    std::cout << "Welcome to my_std_unordered_map! There is an example of unordered_map<const Key, Value> on hashmap with chaining." << std::endl;

    my_std::unordered_map<std::string, std::string> my_unordered_map = {
        {"Car", "BMW"},
        {"Word", "C++"},
        {"Rac", "Volkswagen"}
    };

    std::cout << "unordered_map.insert('Website', 'GitHub');" << std::endl;
    my_unordered_map.insert({ "Website", "GitHub" });
    std::cout << "unordered_map.insert('Website', 'Google');  (create a dublicat)" << std::endl;
    my_unordered_map.insert({ "Website", "Google" });
    std::cout << "unordered_map.insert('Cra', 'Toyota');  (create a collision)" << std::endl;
    my_unordered_map.insert({ "Cra", "Toyota" });
    return 0;
}
/*******************************************************************************
 * back_emplacer, front_emplacer, emplacer & iterators
 * 
 * Author: Yarin Hananiya
 * Date:   23/10/2019
 * ****************************************************************************/
#ifndef EMPLACERS_HPP
#define EMPLACERS_HPP

#include <iterator> // std::output_iterator_tag
#include <memory>   // std::addressof

namespace ilrd
{

/*******************************************************************************
 * back_emplace_iterator 
 ******************************************************************************/
template<class Container>
class back_emplace_iterator
{
public: 
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using container_type = Container;

    constexpr explicit back_emplace_iterator(Container& container);
    ~back_emplace_iterator() = default;

    back_emplace_iterator(const back_emplace_iterator&) = default;  
    back_emplace_iterator(back_emplace_iterator&&) noexcept = default; 
    back_emplace_iterator& operator=(const back_emplace_iterator&) = default;
    back_emplace_iterator& operator=(back_emplace_iterator&&) noexcept = default;

    template<class... Args>
    constexpr back_emplace_iterator& operator=(Args&&... args);

    constexpr back_emplace_iterator& operator*();
    constexpr back_emplace_iterator& operator++();
    constexpr back_emplace_iterator& operator++(int);

private:
    Container *m_container;
};

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr back_emplace_iterator<Container>::
    back_emplace_iterator(Container& container)
: m_container(std::addressof(container))
{}

/*----------------------------------------------------------------------------*/
template<class Container>
template<class... Args>
constexpr back_emplace_iterator<Container>& 
    back_emplace_iterator<Container>::operator=(Args&&... args)
{
    m_container->emplace_back(std::forward<Args>(args)...);

    return *this;
}

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr back_emplace_iterator<Container>&    
    back_emplace_iterator<Container>::operator*()
{
    return *this;
}

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr back_emplace_iterator<Container>& 
    back_emplace_iterator<Container>::operator++()
{
    return *this;
}

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr back_emplace_iterator<Container>& 
    back_emplace_iterator<Container>::operator++(int)
{
    return *this;
}

/*******************************************************************************
 * front_emplace_iterator 
 ******************************************************************************/
template<class Container>
class front_emplace_iterator
{
public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using container_type = Container;

    constexpr explicit front_emplace_iterator(Container& container);
    ~front_emplace_iterator() = default;

    front_emplace_iterator(const front_emplace_iterator&) = default;  
    front_emplace_iterator(front_emplace_iterator&&) noexcept = default; 
    front_emplace_iterator& operator=(const front_emplace_iterator&) = default;
    front_emplace_iterator& operator=(front_emplace_iterator&&) noexcept = default;

    template<class... Args>
    constexpr front_emplace_iterator& operator=(Args&&... args);

    constexpr front_emplace_iterator& operator*();
    constexpr front_emplace_iterator& operator++();
    constexpr front_emplace_iterator& operator++(int);

private:
    Container *m_container;
};

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr front_emplace_iterator<Container>::
    front_emplace_iterator(Container& container)
: m_container(std::addressof(container))
{}

/*----------------------------------------------------------------------------*/
template<class Container>
template<class... Args>
constexpr front_emplace_iterator<Container>& 
    front_emplace_iterator<Container>::operator=(Args&&... args)
{
    m_container->emplace_front(std::forward<Args>(args)...);

    return *this;
}

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr front_emplace_iterator<Container>&    
    front_emplace_iterator<Container>::operator*()
{
    return *this;
}

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr front_emplace_iterator<Container>& 
    front_emplace_iterator<Container>::operator++()
{
    return *this;
}

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr front_emplace_iterator<Container>& 
    front_emplace_iterator<Container>::operator++(int)
{
    return *this;
}

/*******************************************************************************
 * emplace_iterator 
 ******************************************************************************/
template<class Container>
class emplace_iterator
{
public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using container_type = Container;

    constexpr explicit emplace_iterator(Container& container,
                                        typename Container::iterator iter);
    ~emplace_iterator() = default;

    emplace_iterator(const emplace_iterator&) = default;  
    emplace_iterator(emplace_iterator&&) noexcept = default; 
    emplace_iterator& operator=(const emplace_iterator&) = default;
    emplace_iterator& operator=(emplace_iterator&&) noexcept = default;

    template<class Container_ = Container,
             typename = std::enable_if_t<std::is_member_function_pointer_v<decltype(&Container_::key_comp)> >,
             class... Args>
    constexpr emplace_iterator& operator=(Args&&... args)
    {
        m_iter = m_container->emplace_hint(m_iter, std::forward<Args>(args)...);
        ++m_iter;

        return *this;
    }

    template<class... Args>
    constexpr emplace_iterator& operator=(Args&&... args);

    constexpr emplace_iterator& operator*();
    constexpr emplace_iterator& operator++();
    constexpr emplace_iterator& operator++(int);

private:
    Container *m_container;
    typename Container::iterator m_iter;
};

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr emplace_iterator<Container>::
    emplace_iterator(Container& container, 
                     typename Container::iterator iter)
: m_container(std::addressof(container))
, m_iter(iter)
{}

/*----------------------------------------------------------------------------*/
template<class Container>
template<class... Args>
constexpr emplace_iterator<Container>& 
    emplace_iterator<Container>::operator=(Args&&... args)
{
    m_iter = m_container->emplace(m_iter, std::forward<Args>(args)...);
    ++m_iter;

    return *this;
}

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr emplace_iterator<Container>& emplace_iterator<Container>::operator*()
{
    return *this;
}

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr emplace_iterator<Container>& emplace_iterator<Container>::operator++()
{
    return *this;
}

/*----------------------------------------------------------------------------*/
template<class Container>
constexpr emplace_iterator<Container>& 
    emplace_iterator<Container>::operator++(int)
{
    return *this;
}

/*******************************************************************************
 * back_emplacer, front_emplacer, emplacer 
 ******************************************************************************/
template<class Container>
back_emplace_iterator<Container> back_emplacer(Container& container)
{
    return back_emplace_iterator<Container>(container);
}

/*----------------------------------------------------------------------------*/
template<class Container>
front_emplace_iterator<Container> front_emplacer(Container& container)
{
    return front_emplace_iterator<Container>(container);
}

/*----------------------------------------------------------------------------*/
template<class Container>
emplace_iterator<Container> emplacer(Container& container, 
                                     typename Container::iterator iter)
{
    return emplace_iterator<Container>(container, iter);
}

} // namespace ilrd

#endif // EMPLACERS_HPP
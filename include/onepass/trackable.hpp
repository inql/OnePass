#ifndef TRACKABLE_HPP
#define TRACKABLE_HPP

namespace onepass
{
  namespace core
  {
    template<class T>
    class Trackable
    {
     private:
      unsigned id_;
      time_t created_;
      time_t accessed_;
      friend class boost::serialization::access;

     public:
      T _val;
      Trackable() : id_(0)
      {
      }
      Trackable(unsigned i) : id_(i)
      {
        initialize();
      }
      Trackable(unsigned i, T tracked) : id_(i), _val(tracked)
      {
        initialize();
      }
      template<typename Archive>
      void serialize(Archive &ar, const unsigned int)
      {
        ar &id_;
        ar &created_;
        ar &accessed_;
        ar &_val;
      }
      unsigned getId() const
      {
        return id_;
      }
      time_t getCreated() const
      {
        return created_;
      }
      time_t getAccessed() const
      {
        return accessed_;
      }
      void initialize()
      {
        created_ = accessed_ = time(0);
      }
      void seen()
      {
        accessed_ = time(0);
      }
      std::string toString(time_t t)
      {
        char buffer[32];
        std::tm *pmt = std::localtime(&t);
        std::strftime(buffer, 32, "%Y-%m-%d %H:%M:%S", pmt);
        return std::string{ buffer };
      }
    };

  }  // namespace core
}  // namespace onepass

#endif  // TRACKABLE_HPP
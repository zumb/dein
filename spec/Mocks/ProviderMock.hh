<?hh //strict
namespace spec\Dein;

use Dein\Interfaces\Provider;
use Dein\Reflection\ClassInspector;

class ProviderMock implements Provider<\stdClass>
{
  public function get(ClassInspector<\stdClass> $class):\stdClass
  {
    return new \stdClass();
  }
}

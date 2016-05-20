<?hh //strict
namespace spec\Zumb\Dein;

use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\Reflection\ClassInspector;

class ProviderMock implements Provider<\stdClass>
{
  public function get(ClassInspector<\stdClass> $class):\stdClass
  {
    return new \stdClass();
  }
}

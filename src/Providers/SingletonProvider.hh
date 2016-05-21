<?hh //strict
namespace Zumb\Dein\Providers;

use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\Reflection\ClassInspector;

class SingletonProvider<Tc> implements Provider<Tc>
{
  public function __construct(
    protected Tc $singleton
  ) {}

  public function get(ClassInspector<Tc> $class, ...):Tc
  {
    return $this->singleton;
  }
}

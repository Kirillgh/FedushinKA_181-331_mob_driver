from django.urls import include, path
from rest_framework.routers import SimpleRouter
from .quickstart import views
from django.conf.urls import url
from rest_framework_swagger.views import get_swagger_view

schema_view = get_swagger_view(title='Test API')


class OptionalSlashRouter(SimpleRouter):
    def __init__(self):
        super().__init__()
        self.trailing_slash = '/?'


router = OptionalSlashRouter()
router.register(r'users', views.UserViewSet)
router.register(r'clients', views.User2ViewSet, basename='list')

# Wire up our API using automatic URL routing.
# Additionally, we include login URLs for the browsable API.
urlpatterns = [
    path('', include(router.urls)),
    path('api-auth/', include('rest_framework.urls', namespace='rest_framework')),
    url('swagger/', schema_view),
]
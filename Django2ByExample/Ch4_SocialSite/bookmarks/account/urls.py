from django.urls import path
from django.contrib.auth import views as auth_views
from . import views

urlpatterns = [
    # Post views

    # Previous login view
    #path('login/', views.user_login, name='login'),

    # New login view using built in view
    path('login/', auth_views.LoginView.as_view(), name='login'),
    path('logout/', auth_views.LogoutView.as_view(), name='logout'),

    path('', views.dashboard, name='dashboard'),
]

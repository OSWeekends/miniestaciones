import { createWebHistory, createRouter } from 'vue-router';

import AuthService from '@/services/AuthService';

const NotFound = {
  template:
    "<h1>Oops, it looks like the page you're looking for doesn't exist.</h1>"
};
const routes = [
  {
    path: '/login',
    name: 'Login',
    component: () => import('@/views/Login.vue')
  },
  {
    path: '/profile',
    name: 'Profile',
    component: () => import('@/views/Profile.vue'),
    meta: {
      requiresAuth: true
    }
  },
  {
    path: '/dashboard',
    name: 'Dashboard',
    component: () => import('@/views/Dashboard.vue'),
    meta: {
      requiresAuth: true
    }
  },
  {
    path: '/about',
    name: 'About',
    component: () => import('@/views/About.vue'),
    meta: {
      requiresAuth: true
    }
  },
  { path: '/', redirect: '/dashboard' },
  { path: '/:pathMatch(.*)*', name: 'not-found', component: NotFound }
];

const router = createRouter({
  history: createWebHistory(),
  routes
});

router.resolve({
  name: 'not-found',
  params: { pathMatch: ['not', 'found'] }
});

router.beforeEach((to, from, next) => {
  const requiresAuth = to.matched.some(x => x.meta.requiresAuth);
  const currentUser = AuthService.currentUser;

  if (requiresAuth && !currentUser) {
    next({ path: '/login', query: { redirect: to.fullPath } });
  } else if (!requiresAuth && currentUser) {
    next('/');
  } else if (!requiresAuth && !currentUser) {
    next();
  } else {
    next();
  }
  // if (to.matched.some(route => route.meta.requiresAuth)) {
  //   if (!AuthService.currentUser) {
  //     next({ name: 'Login' });
  //   } else {
  //     next();
  //   }
  // } else {
  //   next();
  // }
});
export default router;
